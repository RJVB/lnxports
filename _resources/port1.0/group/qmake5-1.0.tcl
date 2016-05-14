# -*- coding: utf-8; mode: tcl; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4; truncate-lines: t -*- vim:fenc=utf-8:et:sw=4:ts=4:sts=4
# $Id: qmake5-1.0.tcl 145157 2016-01-27 04:47:20Z mcalhoun@macports.org $

#
# Copyright (c) 2013 The MacPorts Project
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
# This portgroup defines standard settings when using qmake.
#
# Usage:
# PortGroup                     qmake5 1.0
#
# or
# set qt5.prefer_kde            yes
# PortGroup                     qmake5 1.0

PortGroup                       qt5 1.0

if {![info exists qt5.using_kde]} {
    ui_debug "qmake5 PortGroup : no qt5-kde info was provided by the Qt5 PortGroup"
    set qt5.using_kde           no
}

if {${qt5.using_kde}} {

    #configure.cmd                   ${qt_qmake_cmd} -r
    configure.cmd                   ${qt_qmake_cmd}
    configure.pre_args-replace      --prefix=${prefix} PREFIX=${prefix}
    configure.universal_args-delete --disable-dependency-tracking

    # qmake defaults to -mmacosx-version-min=10.6, which implies stdlib is libstdc++, which caused problems
    #    (see https://trac.macports.org/wiki/FAQ#libcpp)
    # override QMAKE_MACOSX_DEPLOYMENT_TARGET set in ${prefix}/libexec/qt5/mkspecs/macx-clang/qmake.conf
    # see #50249
    configure.pre_args-append       "QMAKE_MACOSX_DEPLOYMENT_TARGET=${macosx_deployment_target}"

    if {[variant_exists universal] && [variant_isset universal]} {
        set merger_configure_args(i386)     "CONFIG+=\"x86\" -spec ${qt_qmake_spec_32}"
        set merger_configure_args(x86_64)   "-spec ${qt_qmake_spec_64}"
    }

    # qt5-kde does not currently support a debug variant, but does provide (some) debugging information
    configure.pre_args-append       "CONFIG+=release"   

} else {

    # using the mainstream port:qt5

    PortGroup                       active_variants 1.1

    # with the -r option, the examples do not install correctly (no source code)
    #     the install_sources target is not created in the Makefile(s)
    configure.cmd                   ${qt_qmake_cmd}
    #configure.cmd                   ${qt_qmake_cmd} -r

    configure.pre_args-replace      --prefix=${prefix} "PREFIX=${prefix}"
    configure.universal_args-delete --disable-dependency-tracking

    # specify build configuration (compiler, 32-bit/64-bit, etc.)
    if { ![option universal_variant] || ![variant_isset universal] } {
        configure.args-append -spec ${qt_qmake_spec}
    } else {
        lappend merger_configure_args(i386)   -spec ${qt_qmake_spec_32}
        lappend merger_configure_args(x86_64) -spec ${qt_qmake_spec_64}
    }

    # if qtbase was build as a universal,
    #    QT_ARCH and QT_TARGET_ARCH may be set incorrectly in ${qt_mkspecs_dir}/qconfig.pri,
    #    so set them manually
    if { ![option universal_variant] || ![variant_isset universal] } {
        pre-configure {
            if {[active_variants qt5-qtbase universal ""]} {
                configure.args-append \
                    QT_ARCH=${build_arch} \
                    QT_TARGET_ARCH=${build_arch}
            }
        }
    } else {
        foreach arch ${configure.universal_archs} {
            lappend merger_configure_args(${arch}) \
                QT_ARCH=${arch} \
                QT_TARGET_ARCH=${arch}
        }
    }

    # override QMAKE_MACOSX_DEPLOYMENT_TARGET set in ${prefix}/libexec/qt5/mkspecs/macx-clang/qmake.conf
    # see #50249
    configure.args-append QMAKE_MACOSX_DEPLOYMENT_TARGET=${macosx_deployment_target}

    if {![info exists qt5_qmake_request_no_debug]} {
        variant debug description {Build both release and debug libraries} {}

        # accommodating variant request varies depending on how qtbase was built
        pre-configure {

            # determine if qmake builds debug libraries by default (set via variants)
            if {[active_variants qt5-qtbase debug ""]} {
                set base_debug true
            } else {
                set base_debug false
            }

            # determine if the user wants to build debug libraries
            if { [variant_exists debug] && [variant_isset debug] } {
                set this_debug true
            } else {
                set this_debug false
            }

            # determine of qmake's default and user requests are compatible; override qmake if necessary
            if { ${this_debug} && !${base_debug}  } {
                configure.args-append "QT_CONFIG+=\"debug_and_release build_all\""
            }

            if { !${this_debug} && ${base_debug}  } {
                configure.args-append "QT_CONFIG-=\"debug_and_release build_all\" CONFIG-=\"debug\""
            }
        }
    }

}

# override C++11 flags set in ${prefix}/libexec/qt5/mkspecs/common/clang-mac.conf
#    so value of ${configure.cxx_stdlib} can always be used
if {${configure.cxx_stdlib} ne ""} {
    if {${configure.cxx_stdlib} ne "libc++"} {
        configure.args-append \
            QMAKE_CXXFLAGS_CXX11-=-stdlib=libc++ \
            QMAKE_LFLAGS_CXX11-=-stdlib=libc++   \
            QMAKE_CXXFLAGS_CXX11+=-stdlib=${configure.cxx_stdlib} \
            QMAKE_LFLAGS_CXX11+=-stdlib=${configure.cxx_stdlib}
    }
    # ensure ${configure.cxx_stdlib} is used for C++ stdlib
    configure.args-append \
        QMAKE_CXXFLAGS+=-stdlib=${configure.cxx_stdlib} \
        QMAKE_LFLAGS+=-stdlib=${configure.cxx_stdlib}
}

# kate: backspace-indents true; indent-pasted-text true; indent-width 4; keep-extra-spaces true; remove-trailing-spaces modified; replace-tabs true; replace-tabs-save true; syntax Tcl/Tk; tab-indents true; tab-width 4;
