PREFERRED_PROVIDER_virtual/gpu = "mali-t62x"
PREFERRED_PROVIDER_virtual/egl = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgbm = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgles1 = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libgles2 = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libopencl = "${PREFERRED_PROVIDER_virtual/gpu}"
PREFERRED_PROVIDER_virtual/libwayland-egl = "${PREFERRED_PROVIDER_virtual/gpu}"

MALI = "\
    kernel-module-mali-t62x \
    ${PREFERRED_PROVIDER_virtual/gpu} \
"
