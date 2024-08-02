set(SRC_LIST
  main.c
)

add_executable(SystemTest
  ${SRC_LIST}
)

set(LIB_LIST
  Gravity
  GUtilities
  SatelliteBody
  CelestialBody
  BodyMgr
)

target_link_libraries(SystemTest ${LIB_LIST})

set_target_properties(SystemTest PROPERTIES LINKER_LANGUAGE CXX)
