#!/bin/sh

PYTHONPATH="@PREFIX@/lib/python@BRANCH@/site-packages:${PYTHONPATH}"
export PYTHONPATH
export PYTHONPATH
EXE="`basename $0`"

exec /usr/bin/${EXE} "$@"
