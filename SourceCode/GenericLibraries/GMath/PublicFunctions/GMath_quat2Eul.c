/*
 *    @File:         GMath_quat2Eul.c
 *
 *    @Brief:        GMath function which finds euler angles from a quaternion
 *
 *    @Date:         16/05/2024
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

int GMath_quat2Eul(
    double *p_quaternionVector_in,
    double *p_eulerAnglesVector_rad_out)
{
  /* Define local variables */
  double quaternion_x;
  double quaternion_y;
  double quaternion_z;
  double quaternion_s;

  /* Extract quaternion components */
  quaternion_x = *(p_quaternionVector_in + 0);
  quaternion_y = *(p_quaternionVector_in + 1);
  quaternion_z = *(p_quaternionVector_in + 2);
  quaternion_s = *(p_quaternionVector_in + 3);

  /* Find output Euler Angles */
  *(p_eulerAnglesVector_rad_out + 0) = atan2(
      (2 * quaternion_y * quaternion_z + 2 * quaternion_s * quaternion_x),
      (2 * quaternion_s * quaternion_s + 2 * quaternion_z * quaternion_z - 1));

  *(p_eulerAnglesVector_rad_out + 1) =
      asin(-2 * (quaternion_x * quaternion_z + quaternion_s * quaternion_y));

  *(p_eulerAnglesVector_rad_out + 2) = atan2(
      (2 * quaternion_x * quaternion_y + 2 * quaternion_s * quaternion_z),
      (2 * quaternion_s * quaternion_s + 2 * quaternion_x * quaternion_x - 1));

  return GCONST_TRUE;
}
