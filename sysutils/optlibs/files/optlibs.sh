#!/usr/bin/env bash

MPPREFIX="@PREFIX@"
DIRS="${MPPREFIX}"
LIBDIRS=""

for d in ${DIRS} ;do
	for sd in lib lib/x86_64-linux-gnu libexec/qt5/lib ;do
		if [ -d ${d}/${sd} ] ;then
			case ${LD_LIBRARY_PATH} in
				*${d}/${sd}*)
					# already included
					;;
				*)
					if [ "${LIBDIRS}" = "" ] ;then
						LIBDIRS="${d}/${sd}"
					else
						LIBDIRS="${LIBDIRS}:${d}/${sd}"
					fi
					;;
			esac
		fi
	done
done

if [[ "${PATH}" != *"${MPPREFIX}"* ]]; then
	echo "adding ${MPPREFIX} to PATH" 1>&2
	export PATH="${MPPREFIX}/bin:${MPPREFIX}/sbin:${PATH}"
fi

case $0 in
	kdeinit*|klaunch*|kded*)
		LIBDIRS="${LIBDIRS}:${MPPREFIX}/lib/samba"
		;;
esac
if [ "${LD_LIBRARY_PATH}" != "" ] ;then
	export LD_LIBRARY_PATH="${LIBDIRS}:${LD_LIBRARY_PATH}"
else
	export LD_LIBRARY_PATH="${LIBDIRS}"
fi
if [ -x ${MPPREFIX}/lib/libwrapped_syscalls.so ] ;then
	if [ "${LD_PRELOAD}" != "" ] ;then
		export LD_PRELOAD="${MPPREFIX}/lib/libwrapped_syscalls.so:${LD_PRELOAD}"
	else
		export LD_PRELOAD="${MPPREFIX}/lib/libwrapped_syscalls.so"
	fi
fi

APP="$1"
shift 1
exec "${APP}" "$@"
