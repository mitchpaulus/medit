# perf/

Performance testing scaffolding for medit. Workflow is "open a file, mess
around in the editor, quit, then ask Claude to analyze the artifact."
Every run is labeled so you can always re-read the same data later.

## Quick start

```sh
# Drop a representative file somewhere convenient (perf/sample.* is gitignored).
cp /path/to/largish.go perf/sample.go

# Capture a labeled run:
bash perf/run.sh perf/sample.go baseline
# (Editor opens. Drive it for ~5–10s, then :q to quit.)

# Summary:
bash perf/analyze.sh baseline
```

The trace lands at `perf/runs/baseline.log`. As many labels as you want;
nothing is overwritten unless you reuse a label.

## All-the-commands cheatsheet

```sh
bash perf/run.sh perf/sample.go                  # → runs/last.log
bash perf/run.sh perf/sample.go baseline         # → runs/baseline.log
bash perf/run.sh perf/sample.go 'with fix A'     # → runs/with fix A.log

bash perf/analyze.sh                             # list available runs
bash perf/analyze.sh baseline                    # show summary for that label
bash perf/analyze.sh perf/runs/last.log          # works with explicit paths too
```

## Typical before/after flow

```sh
bash perf/run.sh perf/sample.go baseline      # measure current state
# (Claude implements a fix.)
bash perf/run.sh perf/sample.go fix-a         # measure with the fix
# Claude reads both:
bash perf/analyze.sh baseline
bash perf/analyze.sh fix-a
```

Labels are just file names under `perf/runs/`, so they accumulate across
sessions. Delete `perf/runs/<label>.log` to discard a measurement.

## Trace file format

`MEDIT_TRACE=<path>` makes medit append one tab-separated line per frame:

```
frame   total_us=<n>   handle_us=<n>   render_us=<n>   collects=<n>   collect_us=<n>   bytes=<n>
```

- **total_us**: handle + render + everything between. Wall time per frame.
- **handle_us**: time in `handle_normal`/`handle_insert`/etc.
- **render_us**: `render_all` + `ensure_visible`.
- **collects**: number of `collect_bytes()` calls — the suspected hot spot.
- **collect_us**: total time in `collect_bytes()` for the frame.
- **bytes**: current buffer length.

Lines starting with `#` are comments. Frame timing starts *after* the
blocking stdin read so input wait isn't counted.
