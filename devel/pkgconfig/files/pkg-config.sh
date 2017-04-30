#!/bin/sh

if [ "${PKG_CONFIG_MACPORTS_ONLY}" = "" ] ;then
	if [ "${PKG_CONFIG}" = "" -o "${PKG_CONFIG}" = $0 ] ;then
		PKG_CONFIG_SYS="/usr/bin/pkg-config"
	else
		PKG_CONFIG_SYS="${PKG_CONFIG}"
	fi
	if [ "${PKG_CONFIG_PATH}" != "" ] ;then
		PKG_CONFIG_PATH="@PREFIX@/lib/pkgconfig:@PREFIX@/share/pkgconfig:@PREFIX@/lib/@BUILDARCH@-linux-gnu/pkgconfig:${PKG_CONFIG_PATH}"
	else
		PKG_CONFIG_PATH="@PREFIX@/lib/pkgconfig:@PREFIX@/share/pkgconfig:@PREFIX@/lib/@BUILDARCH@-linux-gnu/pkgconfig"
	fi
	export PKG_CONFIG_PATH
	exec "${PKG_CONFIG_SYS}" "$@"
else
	exec pkg-config-mp "$@"
fi
