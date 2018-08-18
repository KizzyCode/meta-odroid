SUMMARY = "Open Source Mali Midgard GPU Kernel Drivers"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://driver/product/kernel/license.txt;md5=13e14ae1bd7ad5bff731bba4a31bb510"

inherit kernel-arch
inherit pkgconfig
inherit module

PACKAGE_ARCH = "${MACHINE_ARCH}"

S = "${WORKDIR}/git"

do_configure[depends] += "virtual/kernel:do_shared_workdir openssl-native:do_populate_sysroot"
do_compile[depends] += "virtual/kernel:do_compile_kernelmodules"

DEPENDS += "bc-native"

EXTRA_OEMAKE = ' HOSTCC="${BUILD_CC} ${BUILD_CFLAGS} ${BUILD_LDFLAGS}" HOSTCPP="${BUILD_CPP}"'

do_configure() {
        unset CFLAGS CPPFLAGS CXXFLAGS LDFLAGS
        oe_runmake CC="${KERNEL_CC}" LD="${KERNEL_LD}" AR="${KERNEL_AR}" \
                   -C ${STAGING_KERNEL_DIR} O=${STAGING_KERNEL_BUILDDIR} scripts prepare

}

do_compile() {
	oe_runmake -C ${STAGING_KERNEL_DIR} \
		M=$(pwd)/driver/product/kernel/drivers/gpu/arm/midgard \
		O=${STAGING_KERNEL_BUILDDIR} \
		EXTRA_CFLAGS="${MALI_FLAGS}" \
		${MALI_KCONFIG}
}

do_install() {
	oe_runmake -C ${STAGING_KERNEL_DIR} \
		M=$(pwd)/driver/product/kernel/drivers/gpu/arm/midgard \
		INSTALL_MOD_PATH="${D}" \
		O=${STAGING_KERNEL_BUILDDIR} \
		EXTRA_CFLAGS="${MALI_FLAGS}" \
		${MALI_KCONFIG} \
		modules_install
}

COMPATIBLE_MACHINE = "odroid-xu3|odroid-xu3-lite|odroid-xu4"
