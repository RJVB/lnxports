# -*- coding: utf-8; mode: tcl; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- vim:fenc=utf-8:filetype=tcl:et:sw=4:ts=4:sts=4

# This PG provides utility code for ports that need to (potentially) install GConf
# settings files on systems where port:gconf proxies the host package.
#
# That means Linux, for now. And that ${prefix}/share/GConf is a symlink to the
# host/system location.
#
# It is a patently bad idea to use parallel GConf installations - for system-wide
# settings at least.
#
# ProxiedGConf::gconf_files : files installed by ${subport} into ${prefix}/share/GConf/gsettings
# ProxiedGConf::handled_since_version : the ${version} of ${subport} that first
#                                       used this PortGroup.
#
# Earlier versions of ${subport} installed their files into GConf/gsettings, which
# we have to assume worked. If these are identical to the ones installed by the current
# version we have to "liberate" them from the MacPorts registry, i.e. keep them installed
# but not registered. So, we install them under a different name and then copy them to
# the expected name in the post-activate
#
# Those files that already exist but don't belong to us AND are identical will be left alone
# and not (re)installed by ${subport}.
#
# If any of the files in question already exist with a different content, we install a versioned
# copy.

namespace eval ProxiedGConf {
}
options ProxiedGConf::gconf_files \
        ProxiedGConf::handled_since_version
default ProxiedGConf::gconf_files           {}
default ProxiedGConf::handled_since_version -1

if {${os.platform} ne "darwin"} {
    proc ProxiedGConf::Installer {} {
        global prefix destroot subport version

        depends_run-append port:gconf

        post-destroot {
           if {[file type ${prefix}/share/GConf] eq "link"} {
              ui_warn "This must be a linux install where port:gconf proxies the host package"
              if {![catch {set vers [lindex [registry_active ${subport}]]}]
                 && [vercmp [lindex ${vers} 1] [option ProxiedGConf::handled_since_version]] < 0} {
                 set ignore_own yes
              }
              foreach f {*}[option ProxiedGConf::gconf_files] {
                 set file ${prefix}/share/GConf/gsettings/${f}
                 if {[file exists ${file}]} {
                    set port [registry_file_registered ${file}]
                    if {${port} != 0 && ![tbool ignore_own]} {
                        ui_msg "${f} is already installed by port:${port}"
                    } else {
                        ui_info "${f} is owned by a host package"
                        if {[catch {exec cmp ${destroot}${file} ${file}}]} {
                           ui_warn "The new ${file} differs from the host version; installing as ${f}.${subport}@${version}"
                           file rename ${destroot}${file} ${destroot}${file}.${subport}@${version}
                        } else {
                           if {[tbool ignore_own]} {
                              ui_warn "${file} was installed by us but needs to be restored"
                              file rename ${destroot}${file} ${destroot}${file}.toberestored_${subport}
                           } else {
                              ui_info "${file} already exists and is identical; not reinstalling"
                              file delete ${destroot}${file}
                           }
                        }
                    }
                 }
              }
           }
        }
        post-activate {
           if {[file type ${prefix}/share/GConf] eq "link"} {
              foreach f [glob -nocomplain ${prefix}/share/GConf/gsettings/*.toberestored_${subport}] {
                 set rf [file rootname ${f}]
                 ui_warn "Restoring ${rf}"
                 file copy ${f} ${rf}
              }
           }
        }
    }

    port::register_callback ProxiedGConf::Installer
}
