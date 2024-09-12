set(SRC_LIST
  main.c
)

add_executable(ModuleUnitTest
  ${SRC_LIST}
)

set(LIB_LIST
  Igrf
)

target_link_libraries(ModuleUnitTest ${LIB_LIST})

set_target_properties(ModuleUnitTest PROPERTIES LINKER_LANGUAGE CXX)
