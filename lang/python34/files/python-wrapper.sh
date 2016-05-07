#!/bin/sh

PYTHONPATH="@PREFIX@/lib/python@BRANCH@/site-packages:${PYTHONPATH}"
export PYTHONPATH

exec /usr/bin/python@SUFFIX@ "$@"