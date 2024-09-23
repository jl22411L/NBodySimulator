add_library(GLegendrePoly
  PublicFunctions/GLegendrePoly_findArrayOutput.c
  PublicFunctions/GLegendrePoly_findAssociatedArrayOutput.c
  PublicFunctions/GLegendrePoly_findAssociatedDerivitiveArrayOutput.c
  PublicFunctions/GLegendrePoly_findSingleOutput.c
)

target_link_libraries(GLegendrePoly
  PRIVATE GMath
)
