set(SRC_LIST
  main.c
)

add_executable(RigidBodyTest
  ${SRC_LIST}
)

set(LIB_LIST
  RigidBody
  GParser
  GConversions
)

target_link_libraries(RigidBodyTest ${LIB_LIST})

set_target_properties(RigidBodyTest PROPERTIES LINKER_LANGUAGE CXX)
