#!/bin/sh

export XDG_CURRENT_DESKTOP=GNOME
exec "@PREFIX@/bin/gnome-control-center.bin" "$@"
