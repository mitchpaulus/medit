//! Filesystem watcher for open files. Each buffer with a backing path
//! registers it here; the underlying `notify` watcher reports any changes
//! to the file (or to its parent directory, since many tools save via
//! atomic-rename which makes the original inode disappear) on a channel
//! that the main loop drains each frame.
//!
//! Cross-platform via the `notify` crate: inotify on Linux,
//! ReadDirectoryChangesW on Windows, FSEvents/kqueue on macOS.

use std::collections::HashSet;
use std::io;
use std::path::{Path, PathBuf};
use std::sync::mpsc;
use std::time::SystemTime;

use notify::{RecommendedWatcher, RecursiveMode, Watcher};

/// Stat snapshot used to detect external changes. Two paths-on-disk are
/// considered "the same content" when both `mtime` and `size` match.
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct DiskMeta {
    pub mtime: SystemTime,
    pub size: u64,
}

impl DiskMeta {
    pub fn read(path: &Path) -> io::Result<Self> {
        let md = std::fs::metadata(path)?;
        Ok(Self {
            mtime: md.modified()?,
            size: md.len(),
        })
    }
}

/// Wraps a `notify` watcher with a non-blocking poll interface tailored
/// to the editor's frame loop. Watches the *parent directory* of each
/// registered path (non-recursively), so atomic-rename saves and editor
/// "delete-then-write" patterns still surface as events on the original
/// filename. Deduplicates parent dirs so we don't error on a second watch.
pub struct FileWatcher {
    watcher: RecommendedWatcher,
    rx: mpsc::Receiver<notify::Result<notify::Event>>,
    watched_dirs: HashSet<PathBuf>,
}

impl FileWatcher {
    pub fn new() -> notify::Result<Self> {
        let (tx, rx) = mpsc::channel();
        let watcher = notify::recommended_watcher(move |res| {
            let _ = tx.send(res);
        })?;
        Ok(Self {
            watcher,
            rx,
            watched_dirs: HashSet::new(),
        })
    }

    /// Register `path` for change notifications. Idempotent — registering
    /// a second file in an already-watched directory is a no-op.
    pub fn watch(&mut self, path: &Path) -> notify::Result<()> {
        let dir = match path.parent() {
            Some(p) if !p.as_os_str().is_empty() => p.to_path_buf(),
            _ => PathBuf::from("."),
        };
        if self.watched_dirs.contains(&dir) {
            return Ok(());
        }
        self.watcher.watch(&dir, RecursiveMode::NonRecursive)?;
        self.watched_dirs.insert(dir);
        Ok(())
    }

    /// Drain pending events. Returns the absolute paths of files that
    /// changed since the last poll; deduplicated. Errors from the watcher
    /// thread are silently dropped — there's no useful recovery and the
    /// editor should keep running.
    pub fn poll(&self) -> Vec<PathBuf> {
        let mut paths: Vec<PathBuf> = Vec::new();
        while let Ok(res) = self.rx.try_recv() {
            if let Ok(event) = res {
                for p in event.paths {
                    if !paths.contains(&p) {
                        paths.push(p);
                    }
                }
            }
        }
        paths
    }
}
