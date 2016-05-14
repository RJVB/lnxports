# -*- coding: utf-8; mode: tcl; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- vim:fenc=utf-8:ft=tcl:et:sw=4:ts=4:sts=4
# kate: backspace-indents true; indent-pasted-text true; indent-width 4; keep-extra-spaces true; remove-trailing-spaces modified; replace-tabs true; replace-tabs-save true; syntax Tcl/Tk; tab-indents true; tab-width 4;
# $Id: qt5-1.0.tcl 113952 2015-06-11 16:30:53Z gmail.com:rjvbertin $
# $Id: qt5-1.0.tcl 113952 2013-11-26 18:01:53Z michaelld@macports.org $

# Copyright (c) 2014 The MacPorts Project
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of Apple Computer, Inc. nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
# This portgroup defines standard settings when using Qt5.
#
# Usage:
# PortGroup     qt5 1.0
#
# or
#
# set qt5.prefer_kde    1
# PortGroup             qt5 1.0

# Check what Qt5 installation flavour already exists, or if not if the port calling us
# indicated a preference. If not, use the default/mainstream port:qt5 .
if {[file exists ${prefix}/include/qt5/QtCore/QtCore]
        && ![info exists qt5.prefer_default]} {
    # Qt5 has been installed through port:qt5-kde and is not the be reinstalled the other way
    ui_debug "Qt5 is provided by port:qt5-kde"
    PortGroup   qt5-kde 1.0
    set qt5.using_kde   yes
} elseif {[file exists ${prefix}/libexec/qt5/plugins]
        && [file type ${prefix}/libexec/qt5/plugins] eq "directory"} {
    # Qt5 has been installed through port:qt5 and is not to be reinstalled the other way
    ui_debug "Qt5 is provided by port:qt5"
    PortGroup   qt5-mac 1.0
    set qt5.using_kde   no
    if {[info exists qt5.prefer_kde] && [info exists building_qt5]} {
        ui_error "You cannot install a Qt5-KDE port with port:qt5 or one of its subports installed!"
        pre-fetch {
            return -code error "Deactivate the conflicting port:qt5 (subports) first!"
        }
        pre-configure {
            return -code error "Deactivate the conflicting port:qt5 (subports) first!"
        }
    }
} elseif {[info exists qt5.prefer_kde]} {
    # The calling port has indicated a preference and no Qt5 port is installed already
    ui_debug "Qt5 will be provided by port:qt5-kde, by request"
    PortGroup   qt5-kde 1.0
    set qt5.using_kde   yes
} else {
    # default fall-back to mainstream port:qt5
    ui_debug "Qt5 will be provided by port:qt5 (default)"
    PortGroup   qt5-mac 1.0
    set qt5.using_kde   no
}

if {!${qt5.using_kde} && [info exists qt5.prefer_kde]} {
    # this is a port that prefers port:qt5-kde and thus expects most of Qt5 to be installed
    # through that single port rather than enumerate all components it depends on.
    depends_lib-append  port:qt5
}

proc qt_branch {} {
    global version
    return [join [lrange [split ${version} .] 0 1] .]
}

# a procedure for declaring dependencies on Qt5 components, which will expand them
# into the appropriate subports for the Qt5 flavour installed
# e.g. qt5.depends_component qtbase qtsvg qtdeclarative
proc qt5.depends_component {first args} {
    global qt5_component_lib
    global qt5.using_kde
    # join ${first} and (the optional) ${args}
    set args [linsert $args[set list {}] 0 ${first}]
    foreach comp ${args} {
        if {${qt5.using_kde}} {
            set portname "qt5-kde-${comp}"
        } else {
            set portname "qt5-${comp}"
        }
        if {[info exists qt5_component_lib] && [info exists qt5_component_lib(${comp})]} {
            # an explicit dependency pattern was given, e.g. path:foo
            depends_lib-append "$qt5_component_lib(${comp}):${portname}"
        } else {
            depends_lib-append port:${portname}
        }
    }
}
