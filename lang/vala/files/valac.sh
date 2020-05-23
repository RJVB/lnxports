#!/bin/sh

VAPIDIRS=""
for J in @PREFIX@/share/vala*/vapi /usr/share/vala*/vapi ;do
    VAPIDIRS="${VAPIDIRS} --vapidir=${J}"
done
GIRDIRS=""
for J in @PREFIX@/share/gir-1.0 /usr/share/gir-1.0 ;do
    VAPIDIRS="${VAPIDIRS} --girdir=${J}"
done

exec "@PREFIX@/bin/`basename $0`-@VERSION@" "$@" ${VAPIDIRS} ${GIRDIRS}
