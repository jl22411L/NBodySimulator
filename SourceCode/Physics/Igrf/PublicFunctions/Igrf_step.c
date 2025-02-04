/*!
 *    @File:         Igrf_step.c
 *
 *    @Brief:        Function which will step the IGRF model and output the
 *                   magnetic field vector.
 *
 *    @Date:         22/10/2024
 *
 */

#include <math.h>

/* Function Includes */
#include "Igrf/PrivateFunctions/Igrf_PrivateFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLegPoly/GLegPoly.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Igrf_step(Igrf_Params *p_igrf_params_in,
              double      *p_sphericalCoordinates_GeoCen_m_in,
              double       primaryBodyRadius_m_in,
              double       simTime_s_in,
              double      *p_magneticFieldVector_Ned_nT_out)
{
  /* Declare local variables */
  double associatedLegPoly[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double associatedLegPolyDerivitive[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double sphericalSecondaryBodyPosition_GeoCent_m[3];

  /* Clear Buffers */
  GZero(&sphericalSecondaryBodyPosition_GeoCent_m[0], double[3]);
  GZero(&associatedLegPoly[0][0],
        double[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1]);
  GZero(&associatedLegPolyDerivitive[0][0],
        double[IGRF_MAX_DEGREE][IGRF_MAX_DEGREE]);

  /* Find spherical coordiantes with Colatitude */
  sphericalSecondaryBodyPosition_GeoCent_m[0] =
      *(p_sphericalCoordinates_GeoCen_m_in + 0);
  sphericalSecondaryBodyPosition_GeoCent_m[1] =
      *(p_sphericalCoordinates_GeoCen_m_in + 1);
  sphericalSecondaryBodyPosition_GeoCent_m[2] =
      GCONST_PI / 2 - *(p_sphericalCoordinates_GeoCen_m_in + 2);

  /* Check tolerances on Colatitude are acceptable */
  Igrf_checkTolerances(&(sphericalSecondaryBodyPosition_GeoCent_m[0]));

  /* Find associated legendre polynomials */
  GLegPoly_associatedLegendreArrayPolynomials(
      &associatedLegPoly[0][0],
      cos(sphericalSecondaryBodyPosition_GeoCent_m[2]),
      p_igrf_params_in->nMaxDegree);

  /* Find derivitive associated legendre polynomials */
  GLegPoly_associatedLegendreArrayPolynomialsDerivitive(
      &associatedLegPolyDerivitive[0][0],
      &associatedLegPoly[0][0],
      cos(sphericalSecondaryBodyPosition_GeoCent_m[2]),
      p_igrf_params_in->nMaxDegree);

  /* Find magnetic field vector in NED coordinate system */
  Igrf_findMagneticFieldInNed(p_magneticFieldVector_Ned_nT_out,
                              &sphericalSecondaryBodyPosition_GeoCent_m[0],
                              &associatedLegPoly[0][0],
                              &associatedLegPolyDerivitive[0][0],
                              primaryBodyRadius_m_in,
                              simTime_s_in,
                              p_igrf_params_in);

  return GCONST_TRUE;
}
