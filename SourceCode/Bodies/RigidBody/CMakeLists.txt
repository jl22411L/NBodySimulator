add_library(RigidBody
  PrivateFunctions/RigidBody_createArchives.c
  PublicFunctions/RigidBody_archiveData.c
  PublicFunctions/RigidBody_findAngularAcceleration.c
  PublicFunctions/RigidBody_init.c
  PublicFunctions/RigidBody_step.c
  PublicFunctions/RigidBody_terminate.c
)

target_link_libraries(RigidBody
    PRIVATE GParser
    PRIVATE GArchive
    PRIVATE GMath
    PRIVATE GIntegral
)
