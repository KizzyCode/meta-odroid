SUMMARY = "Basic Odroid X11 graphics image"

IMAGE_FEATURES += "splash debug-tweaks ssh-server-openssh tools-debug x11"

LICENSE = "MIT"

inherit core-image distro_features_check extrausers
# populate_sdk_qt5

# let's make sure we have a good image..
REQUIRED_DISTRO_FEATURES = "x11"

MALI ?= ""

GTS = "\
     gstreamer1.0 \
     gstreamer1.0-plugins-good \
"

QT5 = "\
    packagegroup-qt5 \
    packagegroup-qt5-apps \
    packagegroup-fonts-truetype \
"

CORE_IMAGE_BASE_INSTALL += " \
    ${XSERVER} \
    ${MALI} \
    ${GTS} \
    ${QT5} \
    ${@bb.utils.contains('MACHINE_FEATURES', 'mali', '${MALI} ', '', d)} \
    ${@bb.utils.contains('DISTRO_FEATURES', 'opengl', '${VIRTUAL-RUNTIME_mesa}', '', d)} \
    xserver-common \
    kernel-modules \
    ttf-dejavu-sans \
    ttf-dejavu-sans-mono \
"

COMPATIBLE_MACHINE = "(odroid-xu3|odroid-xu4|odroid-xu3-lite)"
