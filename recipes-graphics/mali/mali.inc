LICENSE = "Proprietary"
SECTION = "libs"

DEPENDS += "${@bb.utils.contains("DISTRO_FEATURES", "opengl", "virtual/mesa", " ", d)}"
DEPENDS += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "virtual/mesa wayland", " ", d)}"
DEPENDS += "${@bb.utils.contains("DISTRO_FEATURES", "x11", " virtual/libx11 libxext libdrm libxfixes libxdamage", " ", d)}"

PROVIDES += "${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'virtual/egl virtual/libgles1 virtual/libgles2', '', d)}"
PROVIDES += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "virtual/libgbm virtual/libwayland-egl", " ", d)}"

INSANE_SKIP_${PN} = "ldflags dev-so"

INHIBIT_PACKAGE_DEBUG_SPLIT = "1"
INHIBIT_PACKAGE_STRIP = "1"

USE_X11 = "${@bb.utils.contains("DISTRO_FEATURES", "x11", "yes", "no", d)}"
USE_DFB = "${@bb.utils.contains("DISTRO_FEATURES", "directfb", "yes", "no", d)}"
USE_WL = "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "yes", "no", d)}"

do_configure[noexec] = "1"
do_compile[noexec] = "1"

# Shared libs from mali package build aren't versioned, so we need
# to force the .so files into the runtime package (and keep them
# out of -dev package).
FILES_SOLIBSDEV = ""
FILES_${PN} += "${libdir}/*.so"

RREPLACES_${PN} += "libegl libegl1 libgles1 libgles2 libglesv2-2"
RREPLACE_${PN} += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "libgbm libwayland-egl", " ", d)}"
RPROVIDES_${PN} += "libegl libegl1 libgles1 libgles2 libglesv2-2 "
RPROVIDES_${PN} += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "libgbm libwayland-egl", " ", d)}"
RCONFLICTS_${PN} += "libegl libegl1 libgles1 libgles2 libglesv2-2"
RCONFLICTS_${PN} += "${@bb.utils.contains("DISTRO_FEATURES", "wayland", "libgbm libwayland-egl", " ", d)}"

PACKAGE_ARCH = "${MACHINE_ARCH}"
PACKAGES = "${PN} ${PN}-dev"
