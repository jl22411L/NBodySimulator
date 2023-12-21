# Set list of C files
set(SIMTEST_LIST
    PublicFunctions/main.c
)

# Set executable
add_executable(SimTest
    ${SIMTEST_LIST}
)

# set(LIB_LIST
#     GLibrary
# )
target_link_libraries(SimTest ${LIB_LIST})

set_target_properties(SimTest PROPERTIES LINKER_LANGUAGE CXX)