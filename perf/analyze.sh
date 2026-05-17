#!/usr/bin/env bash
# Summarize a medit trace log. Accepts a label (looked up in perf/runs/)
# or a path. With no argument, lists available runs.
#
#   bash perf/analyze.sh                # list runs/
#   bash perf/analyze.sh baseline       # analyze runs/baseline.log
#   bash perf/analyze.sh path/to/x.log  # analyze a file directly
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
RUNS_DIR="$SCRIPT_DIR/runs"

ARG="${1:-}"
if [ -z "$ARG" ]; then
    echo "Available runs:"
    if [ -d "$RUNS_DIR" ] && [ "$(ls -A "$RUNS_DIR" 2>/dev/null)" ]; then
        ls -1t "$RUNS_DIR" | sed -e 's/\.log$//' -e 's/^/  /'
    else
        echo "  (none)"
    fi
    echo
    echo "usage: bash $0 <label-or-path>"
    exit 0
fi

# Resolve ARG to a log file.
if [ -f "$ARG" ]; then
    LOG="$ARG"
elif [ -f "$RUNS_DIR/${ARG}.log" ]; then
    LOG="$RUNS_DIR/${ARG}.log"
else
    echo "no log found for: $ARG" >&2
    echo "looked at: $ARG" >&2
    echo "looked at: $RUNS_DIR/${ARG}.log" >&2
    exit 1
fi

frames=$(grep -c '^frame' "$LOG" 2>/dev/null || true)
if [ -z "${frames:-}" ] || [ "$frames" -eq 0 ]; then
    echo "=== $LOG ==="
    echo "no frames recorded"
    exit 0
fi

echo "=== $LOG ==="
echo "frames: $frames"

awk -F'\t' '/^frame/ {
    split($2,a,"="); split($3,h,"="); split($4,r,"=")
    split($5,c,"="); split($6,ct,"="); split($7,b,"=")
    tot += a[2]; han += h[2]; ren += r[2]
    cn  += c[2]; ctt += ct[2]
    n++; bytes = b[2]
}
END {
    if (n == 0) { exit }
    printf "buffer:  %d bytes\n", bytes
    print  ""
    print  "Per frame (microseconds, mean):"
    printf "  total:   %d\n", tot/n
    printf "  handle:  %d  (%.1f%%)\n", han/n, 100*han/tot
    printf "  render:  %d  (%.1f%%)\n", ren/n, 100*ren/tot
    printf "  other:   %d  (%.1f%%)\n", (tot-han-ren)/n, 100*(tot-han-ren)/tot
    print  ""
    print  "collect_bytes:"
    printf "  calls/frame: %.2f\n", cn/n
    printf "  usec/frame:  %.1f  (%.1f%% of frame total)\n", ctt/n, 100*ctt/tot
}' "$LOG"

# Percentiles for total time.
TMPSORT="$(mktemp)"
trap 'rm -f "$TMPSORT"' EXIT
awk -F'\t' '/^frame/ {
    split($2,a,"=")
    print a[2]
}' "$LOG" | sort -n > "$TMPSORT"

n="$frames"
echo
echo "Percentiles for frame total (microseconds):"
for p in 50 90 95 99; do
    idx=$(( (n * p + 99) / 100 ))
    [ "$idx" -lt 1 ] && idx=1
    [ "$idx" -gt "$n" ] && idx="$n"
    val=$(sed -n "${idx}p" "$TMPSORT")
    printf "  p%-3d: %s\n" "$p" "$val"
done
max=$(tail -1 "$TMPSORT")
printf "  max:  %s\n" "$max"
