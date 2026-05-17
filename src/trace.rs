//! Optional per-frame timing instrumentation. Enable by setting the
//! `MEDIT_TRACE` env var to a file path before launching:
//!
//! ```text
//! MEDIT_TRACE=/tmp/medit.log cargo run --release -- some.go
//! ```
//!
//! After a session, the file holds one tab-separated `key=value` line per
//! frame. Example one-liners:
//!
//! ```text
//! # Mean / max / count of frame times
//! awk -F'\t' '/^frame/ {
//!     split($2,a,"=");
//!     t+=a[2]; if(a[2]>m)m=a[2]; n++
//! } END { printf "mean=%.0f max=%d n=%d\n", t/n, m, n }' /tmp/medit.log
//! ```
//!
//! Cheap when disabled: `tic()` still calls `Instant::now()` (~25ns on
//! Linux) but `record_*` / `emit_frame` short-circuit on the `OnceLock`
//! check. Negligible compared to anything else the loop is doing.

use std::fs::{File, OpenOptions};
use std::io::Write;
use std::sync::atomic::{AtomicU32, AtomicU64, Ordering};
use std::sync::{Mutex, OnceLock};
use std::time::Instant;

static TRACER: OnceLock<Mutex<File>> = OnceLock::new();
static COLLECT_CALLS: AtomicU32 = AtomicU32::new(0);
static COLLECT_NS: AtomicU64 = AtomicU64::new(0);

/// Read `MEDIT_TRACE` from the environment and, if set, open the file in
/// append mode and stash it globally. Call once at startup.
pub fn init_from_env() {
    let path = match std::env::var("MEDIT_TRACE") {
        Ok(p) => p,
        Err(_) => return,
    };
    let mut f = match OpenOptions::new().create(true).append(true).open(&path) {
        Ok(f) => f,
        Err(_) => return,
    };
    let _ = writeln!(f, "# --- medit trace start ---");
    let _ = TRACER.set(Mutex::new(f));
}

#[inline]
pub fn enabled() -> bool {
    TRACER.get().is_some()
}

#[inline]
pub fn tic() -> Instant {
    Instant::now()
}

#[inline]
pub fn toc(start: Instant) -> u64 {
    start.elapsed().as_nanos() as u64
}

/// Add one observation of `collect_bytes` to the per-frame counters.
/// Cleared on the next `emit_frame` call.
pub fn record_collect(ns: u64) {
    if enabled() {
        COLLECT_CALLS.fetch_add(1, Ordering::Relaxed);
        COLLECT_NS.fetch_add(ns, Ordering::Relaxed);
    }
}

/// Append one frame record to the trace file and reset per-frame counters.
pub fn emit_frame(total_ns: u64, handle_ns: u64, render_ns: u64, bytes_size: usize) {
    let mutex = match TRACER.get() {
        Some(m) => m,
        None => return,
    };
    let collects = COLLECT_CALLS.swap(0, Ordering::Relaxed);
    let collect_ns = COLLECT_NS.swap(0, Ordering::Relaxed);
    if let Ok(mut f) = mutex.lock() {
        let _ = writeln!(
            f,
            "frame\ttotal_us={}\thandle_us={}\trender_us={}\tcollects={}\tcollect_us={}\tbytes={}",
            total_ns / 1000,
            handle_ns / 1000,
            render_ns / 1000,
            collects,
            collect_ns / 1000,
            bytes_size,
        );
    }
}
