/*!
 *    @File:         KeplarianPropogation_findEccentricAnomoly.c
 *
 *    @Brief:        Private function which will find the eccentric anomoly
 *
 *    @Date:         09/03/2025
 *
 */

#include <math.h>
#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Guidance/KeplarianPropogation/ConstantDefs/KeplarianPropogation_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"

int KeplarianPropogation_findEccentricAnomoly(
    double  meanAnomoly_rad_in,
    double  eccentricity_in,
    double *p_eccentricAnomoly_rad_out)
{
  /* Declare local variables */
  double   eccentricAnomolyIterable_rad;
  double   ecentricAnomolyFunctionDerivitive;
  double   eccentricAnomolyFuctionError_rad;
  uint16_t i;

  /* Set first guess of ecentric anomoly to mean anomoly */
  eccentricAnomolyIterable_rad = meanAnomoly_rad_in;

  for (i = 0; i < KEPLARIAN_PROPOGATION_ECCENTRIC_ANOMOLY_MAX_ITERATIONS; i++)
  {
    /* Find the function out of the eccentric anomoly */
    eccentricAnomolyFuctionError_rad =
        (eccentricAnomolyIterable_rad -
         eccentricity_in * sin(eccentricAnomolyIterable_rad) -
         meanAnomoly_rad_in);

    /* Find the tangent line value of the ecentric anomoly */
    ecentricAnomolyFunctionDerivitive =
        1 - eccentricity_in * cos(eccentricAnomolyIterable_rad);

    /* Update the guess for ecentric anomoly */
    eccentricAnomolyIterable_rad -=
        eccentricAnomolyFuctionError_rad / ecentricAnomolyFunctionDerivitive;

    /* If the tolreance has been reached by function output, break loop */
    if (eccentricAnomolyFuctionError_rad <
        KEPLARIAN_PROPOGATION_ECCENTRIC_ANOMOLY_TOLERANCE_RAD)
    {
      break;
    }
  }

  /* Set output of eccentric anomoly to final iteraton */
  *(p_eccentricAnomoly_rad_out) = eccentricAnomolyIterable_rad;

  return GCONST_TRUE;
}