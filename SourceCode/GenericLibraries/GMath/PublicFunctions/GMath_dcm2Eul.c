/*
 *    @File:         GMath_dcm2Eul.c
 *
 *    @Brief:        GMath function to find euler vector from a DCM
 *
 *    @Date:         20/05/2024
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

int GMath_dcm2Eul(double *p_dcmMatrix_in, double *p_eulerAngleVector_rad_out)
{
  /* Declare local variables */
  double a11;
  double a12;
  double a13;
  double a23;
  double a33;

  /* Decompose DCM */
  a11 = *(p_dcmMatrix_in + 0);
  a12 = *(p_dcmMatrix_in + 1);
  a13 = *(p_dcmMatrix_in + 2);
  a23 = *(p_dcmMatrix_in + 5);
  a33 = *(p_dcmMatrix_in + 8);

  /* Find the Euler angles */
  *(p_eulerAngleVector_rad_out + 0) = atan2(a23, a33);
  *(p_eulerAngleVector_rad_out + 1) = asin(-a13);
  *(p_eulerAngleVector_rad_out + 2) = atan2(a12, a11);

  return GCONST_TRUE;
}
