add_library(RigidBody
  PrivateFunctions/RigidBody_archiveData.c
  PrivateFunctions/RigidBody_createArchives.c
  PrivateFunctions/RigidBody_findAngularAcceleration.c
  PrivateFunctions/RigidBody_findTranslationalAcceleration.c
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
