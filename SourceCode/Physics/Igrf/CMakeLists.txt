add_library(Igrf
  PublicFunctions/Igrf_init.c
)

set(LIB_LIST
  GParser
)

target_link_libraries(Igrf ${LIB_LIST})
