set(SRC_LIST
  main.c
)

add_executable(JamSailSimulation
  ${SRC_LIST}
)

set(LIB_LIST
  Gravity
  GUtilities
  SatelliteBody
  CelestialBody
  BodyMgr
  JamSail
  SunSensor
  Magnetometer
)

target_link_libraries(JamSailSimulation ${LIB_LIST})

set_target_properties(JamSailSimulation PROPERTIES LINKER_LANGUAGE CXX)
