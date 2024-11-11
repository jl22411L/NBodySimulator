add_library(SunSensor
  PublicFunctions/SunSensor_init.c
)

set(LIB_LIST
  GParser
  GArchive
)

target_link_libraries(SunSensor ${LIB_LIST})