#Mali userland provides these
PROVIDES_remove = "virtual/libgles1 virtual/libgles2 virtual/egl virtual/libegl"
PROVIDES_remove = "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "virtual/libgbm virtual/libwayland-egl", " ", d)}"


do_install_append () {
    rm -f ${D}/${libdir}/libEGL*
    rm -f ${D}/${libdir}/libGLESv1_CM.*
    rm -f ${D}/${libdir}/libGLESv2.*
    rm -f ${D}/${libdir}/libgbm*
    rm -f ${D}/${libdir}/libwayland-egl*
}
