PREFERRED_PROVIDER_virtual/egl = "mali-t62x"
PREFERRED_PROVIDER_virtual/libgbm = "mali-t62x"
PREFERRED_PROVIDER_virtual/libgles1 = "mali-t62x"
PREFERRED_PROVIDER_virtual/libgles2 = "mali-t62x"
PREFERRED_PROVIDER_virtual/libopencl = "mali-t62x"
PREFERRED_PROVIDER_virtual/libwayland-egl = "mali-t62x"
PREFERRED_PROVIDER_virtual/libgl = "${VIRTUAL-RUNTIME_mesa}"
PREFERRED_PROVIDER_virtual/mesa = "${VIRTUAL-RUNTIME_mesa}"


MALI = "\
    kernel-module-mali-t62x \
    mali-t62x\
"
