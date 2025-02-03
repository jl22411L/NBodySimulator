add_library(Magnetometer
  PrivateFunctions/Magnetometer_createArchives.c
  PublicFunctions/Magnetometer_init.c
)

set(LIB_LIST
  GParser
  GArchive
  Igrf
)

target_link_libraries(Magnetometer ${LIB_LIST})