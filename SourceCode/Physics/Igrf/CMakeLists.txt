add_library(Igrf
  PrivateFunctions/Igrf_loadParams.c
  PrivateFunctions/Igrf_applyNormalisation.c
  PublicFunctions/Igrf_init.c
)

set(LIB_LIST
  GParser
  GLegPoly
)

target_link_libraries(Igrf ${LIB_LIST})
