# Odroid XU default BSP

include conf/machine/include/samsung-exynos.inc
include conf/machine/include/odroid-default-settings.inc

DEFAULTTUNE = "cortexa15hf-neon"
include conf/machine/include/tune-cortexa15.inc

UBOOT_FDT_LOADADDR = "0x40800000"
UBOOT_LOADADDR = "0x40007FC0"
UBOOT_LOADADDRESS = "0x40007FC0"
UBOOT_KERNEL_NAME = "zImage"

WKS_FILE ?= "odroid_xu-u-boot.wks"

MACHINE_FEATURES_append = " alsa screen"

VIRTUAL-RUNTIME_mesa = "mesa" 

require ${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'mali-t62x.inc', '', d)}

XSERVER = " \
    xserver-xorg \
    xf86-video-fbdev \
    ${@bb.utils.contains('DISTRO_FEATURES', 'opengl', 'xserver-xorg-extension-glx', '', d)} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'mali', 'xf86-video-armsoc xserver-xorg-module-exa', '', d)} \
    xf86-input-evdev \
    xf86-input-mouse \
    xf86-input-keyboard \
    xf86-video-modesetting \
    xserver-xorg-module-libint10 \
"
