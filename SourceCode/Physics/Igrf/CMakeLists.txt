add_library(Igrf
  PrivateFunctions/Igrf_applyNormalisation.c
  PrivateFunctions/Igrf_checkTolerances.c
  PrivateFunctions/Igrf_findCoefficients.c
  PrivateFunctions/Igrf_findMagneticFieldInNed.c
  PrivateFunctions/Igrf_loadParams.c
  PublicFunctions/Igrf_init.c
  PublicFunctions/Igrf_step.c
)

set(LIB_LIST
  GParser
  GLegPoly
  GMath
)

target_link_libraries(Igrf ${LIB_LIST})
