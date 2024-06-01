add_library(BodyMgr
  PublicFunctions/BodyMgr_init.c
)

target_link_libraries(BodyMgr
  PRIVATE CelestialBody
  PRIVATE SatelliteBody
  PRIVATE UavBody
  PRIVATE RigidBody
)
