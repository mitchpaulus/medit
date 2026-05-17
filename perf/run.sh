#!/usr/bin/env bash
# Launch medit (release build) with tracing enabled. Output trace is
# written to perf/runs/<label>.log, where <label> defaults to "last" if
# not provided.
#
#   bash perf/run.sh perf/sample.go                 # → perf/runs/last.log
#   bash perf/run.sh perf/sample.go baseline        # → perf/runs/baseline.log
#   bash perf/run.sh perf/sample.go 'with fix A'    # → perf/runs/with fix A.log
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
RUNS_DIR="$SCRIPT_DIR/runs"

if [ $# -lt 1 ]; then
    echo "usage: $0 <path-to-file> [label]" >&2
    exit 1
fi

FILE="$1"
LABEL="${2:-last}"

mkdir -p "$RUNS_DIR"
TRACE_FILE="$RUNS_DIR/${LABEL}.log"

# Truncate any previous content for this label so the new session is the
# only thing recorded.
: > "$TRACE_FILE"

cd "$REPO_ROOT"
MEDIT_TRACE="$TRACE_FILE" cargo run --release --quiet -- "$FILE"

echo
echo "Trace: $TRACE_FILE"
echo "Run    bash $SCRIPT_DIR/analyze.sh '$LABEL'    for a summary."
