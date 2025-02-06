add_library(Gyro
  PrivateFunctions/Gyro_archiveData.c
  PrivateFunctions/Gyro_createArchives.c
  PublicFunctions/Gyro_init.c
  PublicFunctions/Gyro_step.c
)

set(LIB_LIST
  PRIVATE GParser
  PRIVATE GArchive
  PRIVATE GMath
)

target_link_libraries(Gyro ${LIB_LIST})