add_library(RigidBody
  PrivateFunctions/RigidBody_createArchives.c
  PublicFunctions/RigidBody_archiveData.c
  PublicFunctions/RigidBody_init.c
)

target_link_libraries(RigidBody
    PRIVATE GParser
    PRIVATE GArchive
)