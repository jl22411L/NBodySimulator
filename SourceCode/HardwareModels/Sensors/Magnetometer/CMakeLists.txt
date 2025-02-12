add_library(Magnetometer
  PrivateFunctions/Magnetometer_createArchives.c
  PrivateFunctions/Magnetometer_archiveData.c
  PublicFunctions/Magnetometer_init.c
  PublicFunctions/Magnetometer_step.c
)

set(LIB_LIST
  PRIVATE GParser
  PRIVATE GArchive
  PRIVATE Igrf
  PRIVATE GMath
  PRIVATE CelestialBody
  PRIVATE GRand
)

target_link_libraries(Magnetometer ${LIB_LIST})