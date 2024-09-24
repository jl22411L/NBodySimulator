add_library(GLegPoly
  PublicFunctions/GLegePoly_associatedLegendreArrayPolynomials.c
  PublicFunctions/GLegePoly_associatedLegendreArrayPolynomialsDerivitive.c
  PublicFunctions/GLegePoly_legendreArrayPolynomials.c
  PublicFunctions/GLegePoly_legendrePolynomial.c
)

target_link_libraries(GLegPoly
  PRIVATE GMath
)
