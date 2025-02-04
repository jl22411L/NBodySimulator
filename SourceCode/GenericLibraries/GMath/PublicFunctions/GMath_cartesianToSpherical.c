/*!
 *    @File:         GMath_cartesianToSpherical.c
 *
 *    @Brief:        Function which converts a vector from cartesian coordinates
 *                   to sphercal coordinates.
 *
 *    @Date:         04/02/2025
 *
 */

#include <math.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_cartesianToSpherical(double *p_sphericalVector_out,
                               double *p_cartesianVector_in)
{
  /* Declare local variables */
  double x;
  double y;
  double z;

  /* Extract components of cartesian vector */
  x = *(p_cartesianVector_in + 0);
  y = *(p_cartesianVector_in + 1);
  z = *(p_cartesianVector_in + 2);

  *(p_sphericalVector_out + 0) = sqrt(x * x + y * y + z * z);
  *(p_sphericalVector_out + 1) = atan2(y, x);
  *(p_sphericalVector_out + 2) = asin(z / *(p_sphericalVector_out + 0));

  return GCONST_TRUE;
}