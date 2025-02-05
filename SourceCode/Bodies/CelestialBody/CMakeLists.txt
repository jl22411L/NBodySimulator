add_library(CelestialBody
  PrivateFunctions/CelestialBody_createArchives.c
  PrivateFunctions/CelestialBody_findResultantForce.c
  PublicFunctions/CelestialBody_archiveData.c
  PublicFunctions/CelestialBody_checkRotationAngle.c
  PublicFunctions/CelestialBody_init.c
  PublicFunctions/CelestialBody_step.c
  PublicFunctions/CelestialBody_terminate.c
)

target_link_libraries(CelestialBody
  PUBLIC RigidBody
  PRIVATE GArchive
  PRIVATE GParser
)
