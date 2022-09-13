#!/bin/sh

if [ "${PKG_CONFIG_MACPORTS_ONLY}" = "" ] ;then
	if [ "${PKG_CONFIG}" = "" -o "${PKG_CONFIG}" = $0 ] ;then
		PKG_CONFIG_SYS="pkg-config-mp"
		SYSPKG_PATH="`/usr/bin/pkg-config --variable pc_path pkg-config`"
	else
		PKG_CONFIG_SYS="${PKG_CONFIG}"
		SYSPKG_PATH="`${PKG_CONFIG_SYS} --variable pc_path pkg-config`"
	fi
	if [ "${PKG_CONFIG_PATH}" != "" ] ;then
		PKG_CONFIG_PATH="@PREFIX@/lib/pkgconfig:@PREFIX@/share/pkgconfig:@PREFIX@/lib/@BUILDARCH@-linux-gnu/pkgconfig:${PKG_CONFIG_PATH}:${SYSPKG_PATH}"
	else
		PKG_CONFIG_PATH="@PREFIX@/lib/pkgconfig:@PREFIX@/share/pkgconfig:@PREFIX@/lib/@BUILDARCH@-linux-gnu/pkgconfig:${SYSPKG_PATH}"
	fi
	export PKG_CONFIG_PATH
	exec "${PKG_CONFIG_SYS}" "$@"
else
	exec pkg-config-mp "$@"
fi
