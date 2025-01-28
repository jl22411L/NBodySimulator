add_library(JamSail
  PublicFunctions/JamSail_init.c
)

set(LIB_LIST
  PRIVATE BodyMgr
)

target_link_libraries(JamSail ${LIB_LIST})