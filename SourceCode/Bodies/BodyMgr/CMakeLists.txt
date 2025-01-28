add_library(BodyMgr
  PublicFunctions/BodyMgr_findSatelliteBody.c
  PublicFunctions/BodyMgr_init.c
  PublicFunctions/BodyMgr_step.c
  PublicFunctions/BodyMgr_terminate.c
)

target_link_libraries(BodyMgr
  PRIVATE CelestialBody
  PRIVATE SatelliteBody
  PRIVATE UavBody
  PRIVATE RigidBody
)
