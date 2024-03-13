add_library(SatelliteBody
  PrivateFunctions/SatelliteBody_createArchives.c
  PublicFunctions/SatelliteBody_archiveData.c
  PublicFunctions/SatelliteBody_init.c
  PublicFunctions/SatelliteBody_step.c
  PublicFunctions/SatelliteBody_terminate.c
)

target_link_libraries(SatelliteBody
  PUBLIC RigidBody
  PRIVATE GArchive
  PRIVATE GParser
)
