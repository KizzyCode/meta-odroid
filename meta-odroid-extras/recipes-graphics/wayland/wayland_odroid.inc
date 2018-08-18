#Mail userland provides these
PROVIDES_remove = "virtual/libgbm virtual/libwayland-egl"

do_install_append () {
    #rm -f ${D}${libdir}/pkgconfig/wayland-egl.pc
    rm -f ${D}/${libdir}/libgbm*
    rm -f ${D}/${libdir}/libwayland-egl*
}
