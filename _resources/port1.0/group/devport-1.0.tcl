# -*- coding: utf-8; mode: tcl; c-basic-offset: 4; indent-tabs-mode: nil; tab-width: 4; truncate-lines: t -*- vim:fenc=utf-8:et:sw=4:ts=4:sts=4

# Copyright (c) 2015 The MacPorts Project
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
# Usage:
# PortGroup     devport 1.0

namespace eval dev {
    # it shouldn't be necessary to record variants in the archive name
    set archname ${name}@${version}-dev.tar.bz2
    # this could go into the software images directory
    set archdir ${prefix}/var/devcontent
}

options devport_content
default devport_content ""

proc create_devport_content {} {
    global destroot prefix
    set rawargs [option devport_content]
    set args ""
    # convert the arguments to local-relative:
    foreach a ${rawargs} {
        set args "${args} .${a}"
    }
    xinstall -m 755 -d ${destroot}${dev::archdir}
    if {[catch {system -W ${destroot} "bsdtar -cjvf ${destroot}${dev::archdir}/${dev::archname} ${args}"} err]} {
        ui_error "Failure creating ${destroot}${dev::archdir}/${dev::archname} for ${args}: ${err}"
        file delete -force ${destroot}${dev::archdir}/${dev::archname}
    } else {
        foreach a ${args} {
            file delete -force ${destroot}/${a}
        }
    }
}

proc unpack_devport_content {} {
    global destroot prefix
    if {[file exists ${dev::archdir}/${dev::archname}]} {
        if {[catch {system -W ${destroot} "bsdtar -xvf ${dev::archdir}/${dev::archname}"} err]} {
            ui_error "Failure unpacking ${dev::archdir}/${dev::archname}: ${err}"
        }
    } else {
        ui_error "The port's content doesn't exists (${dev::archdir}/${dev::archname})!"
        return -code error "Missing content"
    }
}

proc create_devport {dependency} {
    global name long_description
    subport ${name}-dev {
        description     "Development headers and libraries for ${name}"
        depends_lib-append \
                        ${dependency}
        long_description ${long_description}\nThis installs the development headers and libraries.
        installs_libs   yes
        supported_archs noarch
        distfiles
        fetch {}
        checksum {}
        extract {}
        use_configure   no
        patchfiles
        build {}
        destroot {
            unpack_devport_content
        }
    }
}
