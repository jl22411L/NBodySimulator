set(SRC_LIST
  main.c
)

add_executable(GParser_UnitTest
  ${SRC_LIST}
)

set(LIB_LIST
  GParser
)

target_link_libraries(GParser_UnitTest ${LIB_LIST})

set_target_properties(GParser_UnitTest PROPERTIES LINKER_LANGUAGE CXX)