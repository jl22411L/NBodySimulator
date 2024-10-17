add_library(GLegPoly
  PublicFunctions/GLegPoly_associatedLegendreArrayPolynomials.c
  PublicFunctions/GLegPoly_associatedLegendreArrayPolynomialsDerivitive.c
  PublicFunctions/GLegPoly_findSchmidtQuasiNormFactors.c
  PublicFunctions/GLegPoly_legendreArrayPolynomials.c
  PublicFunctions/GLegPoly_legendrePolynomial.c
)

target_link_libraries(GLegPoly
  PRIVATE GMath
)
