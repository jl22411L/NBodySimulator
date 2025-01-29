add_library(JamSail
  PublicFunctions/JamSail_init.c
  PublicFunctions/JamSail_step.c
)

set(LIB_LIST
  PRIVATE BodyMgr
  PRIVATE SunSensor
)

target_link_libraries(JamSail ${LIB_LIST})