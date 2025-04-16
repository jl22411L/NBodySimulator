/*
 *    @File:         GMath_dcm2Quat.c
 *
 *    @Brief:        GMath function for finding a quaternionfrom a DCM.
 *
 *                   [Ref: https://motoq.github.io/doc/tnotes/dcmq.pdf]
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
#include "GMath/ConstantDefs/GMath_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GMath_dcm2Quat(double *p_dcmMatrix_in, double *p_quaternionVector_out)
{
  /* Define local variables */
  double quaternion_x;
  double quaternion_y;
  double quaternion_z;
  double quaternion_s;
  double a11;
  double a22;
  double a33;
  double a31;
  double a13;
  double a12;
  double a21;
  double a23;
  double a32;

  /* Extract dcm elements */
  a11 = *(p_dcmMatrix_in + 3 * 0 + 0);
  a12 = *(p_dcmMatrix_in + 3 * 0 + 1);
  a13 = *(p_dcmMatrix_in + 3 * 0 + 2);
  a21 = *(p_dcmMatrix_in + 3 * 1 + 0);
  a22 = *(p_dcmMatrix_in + 3 * 1 + 1);
  a23 = *(p_dcmMatrix_in + 3 * 1 + 2);
  a31 = *(p_dcmMatrix_in + 3 * 2 + 0);
  a32 = *(p_dcmMatrix_in + 3 * 2 + 1);
  a33 = *(p_dcmMatrix_in + 3 * 2 + 2);

  /* Find which set of equations is the most stable to convert to DCM */
  if (1 + a11 + a22 + a33 > GMATH_DCM2QUAT_CONVERSION_TOLERANCE)
  {
    /* Find quaternion components */
    quaternion_s = sqrt((1 + a11 + a22 + a33) / 4);
    quaternion_x = -(a23 - a32) / (4 * quaternion_s);
    quaternion_y = -(a31 - a13) / (4 * quaternion_s);
    quaternion_z = -(a12 - a21) / (4 * quaternion_s);
  }
  else if (1 + a11 - a22 - a33 > GMATH_DCM2QUAT_CONVERSION_TOLERANCE)
  {
    /* Find quaternion components */
    quaternion_x = sqrt((1 + a11 - a22 - a33) / 4);
    quaternion_s = -(a23 - a32) / (4 * quaternion_x);
    quaternion_y = -(a12 - a21) / (4 * quaternion_x);
    quaternion_z = -(a31 - a13) / (4 * quaternion_x);
  }
  else if (1 - a11 + a22 - a33)
  {
    /* Find quaternion components */
    quaternion_y = sqrt((1 - a11 + a22 - a33) / 4);
    quaternion_s = -(a31 - a13) / (4 * quaternion_y);
    quaternion_x = -(a12 - a21) / (4 * quaternion_y);
    quaternion_z = -(a23 - a32) / (4 * quaternion_y);
  }
  else if (1 - a11 - a22 + a33)
  {
    /* Find quaternion components */
    quaternion_z = sqrt((1 - a11 - a22 + a33) / 4);
    quaternion_s = -(a12 - a21) / (4 * quaternion_z);
    quaternion_x = -(a31 - a13) / (4 * quaternion_z);
    quaternion_y = -(a23 - a32) / (4 * quaternion_z);
  }
  else
  {
    // TODO: Need to figure out what to do on actual processor
    GError("All posible conversions are less then tolerance %lf",
           GMATH_DCM2QUAT_CONVERSION_TOLERANCE);
  }

  /* Store quaternion components in quaternion */
  *(p_quaternionVector_out + 0) = quaternion_x;
  *(p_quaternionVector_out + 1) = quaternion_y;
  *(p_quaternionVector_out + 2) = quaternion_z;
  *(p_quaternionVector_out + 3) = quaternion_s;

  return GCONST_TRUE;
}
