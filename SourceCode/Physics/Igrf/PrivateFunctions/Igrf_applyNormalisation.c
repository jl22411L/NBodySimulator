/*
 *    @File:         Igrf_applyNormalisation.c
 *
 *    @Brief:        Function which applies the quasi schmidt normalisation to
 *                   gaussian coefficients.
 *
 *    @Date:         21/10/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLegPoly/GLegPoly.h"
#include "GZero/GZero.h"

int Igrf_applyNormalisation(Igrf_Params *p_igrf_params_out)
{
  /* Declare local variables */
  double normalisationCoefficientFactors[IGRF_MAX_DEGREE + 1]
                                        [IGRF_MAX_DEGREE + 1];
  uint8_t n;
  uint8_t m;

  /*!
   * Clear Buffers. Note, the +1 is because the normalisation coefficients
   * include the value for P[0][0] which is not included in the IGRF model.
   * Hence, IGRF_MAX_DEGREE is set to match with the literature, and
   * hence a +1 needs to be included to capture all the normalisation
   * coefficients.
   */
  GZero(&normalisationCoefficientFactors[0][0],
        double[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1]);

  /* Find the normalisation coefficient */
  GLegPoly_findSchmidtQuasiNormFactors(&normalisationCoefficientFactors[0][0],
                                       (p_igrf_params_out->nMaxDegree));

  /* Apply normalisation to coefficients */
  for (n = 1; n <= p_igrf_params_out->nMaxDegree; n++)
  {
    for (m = 0; m <= n; m++)
    {
      /* Apply normalisation to g coefficients */
      p_igrf_params_out->gEpochCoefficients_nT[n][m] *=
          normalisationCoefficientFactors[n][m];

      /* Apply normalisation to h coefficients */
      p_igrf_params_out->hEpochCoefficients_nT[n][m] *=
          normalisationCoefficientFactors[n][m];

      /* Apply normalisation to g linear rate coefficients */
      p_igrf_params_out->gLinearRateCoefficients_nTs[n][m] *=
          normalisationCoefficientFactors[n][m];

      /* Apply normalisation to h linear rate coefficients */
      p_igrf_params_out->hLinearRateCoefficients_nTs[n][m] *=
          normalisationCoefficientFactors[n][m];
    }
  }

  return GCONST_TRUE;
}
