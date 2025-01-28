add_library(SunSensor
  PrivateFunctions/SunSensor_archiveData.c
  PrivateFunctions/SunSensor_checkForBlocking.c
  PrivateFunctions/SunSensor_createArchives.c
  PublicFunctions/SunSensor_init.c
  PublicFunctions/SunSensor_step.c
)

set(LIB_LIST
  GParser
  GArchive
)

target_link_libraries(SunSensor ${LIB_LIST})