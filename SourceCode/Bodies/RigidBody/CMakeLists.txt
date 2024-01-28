add_library(RigidBody
  PublicFunctions/RigidBody_init.c
)

target_link_libraries(RigidBody
    PRIVATE GParser
)