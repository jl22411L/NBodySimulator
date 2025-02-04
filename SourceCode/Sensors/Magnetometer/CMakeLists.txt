add_library(Magnetometer
  PrivateFunctions/Magnetometer_createArchives.c
  PublicFunctions/Magnetometer_init.c
  PublicFunctions/Magnetometer_step.c
)

set(LIB_LIST
  GParser
  GArchive
  Igrf
  GMath
)

target_link_libraries(Magnetometer ${LIB_LIST})