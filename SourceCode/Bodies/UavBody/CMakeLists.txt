add_library(UavBody
  PrivateFunctions/UavBody_createArchives.c
  PublicFunctions/UavBody_archiveData.c
  PublicFunctions/UavBody_init.c
  PublicFunctions/UavBody_step.c
  PublicFunctions/UavBody_terminate.c
)

target_link_libraries(UavBody
  PUBLIC RigidBody
  PRIVATE GArchive
  PRIVATE GParser
)
