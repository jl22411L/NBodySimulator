add_library(KeplarianPropogation
  PrivateFunctions/KeplarianPropogation_findEccentricAnomoly.c
  PrivateFunctions/KeplarianPropogation_findPositionInInertCen.c
  PublicFunctions/KeplarianPropogation_keplarianToCartesian.c
)

set(LIB_LIST
  GMath
)

target_link_libraries(KeplarianPropogation ${LIB_LIST})