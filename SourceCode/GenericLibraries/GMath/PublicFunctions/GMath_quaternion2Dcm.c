/*
 *    @File:         GMath_quat2Dcm.c
 *
 *    @Brief:        GMath function which converts a quaternion into a DCM.
 *
 *    @Date:         20/05/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_quaternion2Dcm(double *p_quaternionVector_in, double *p_dcmMatrix_out)
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

  /* Find elements of rotation matrix */
  *(p_dcmMatrix_out + 0) =
      (quaternion_s * quaternion_s + quaternion_x * quaternion_x -
       quaternion_y * quaternion_y - quaternion_z * quaternion_z);

  *(p_dcmMatrix_out + 1) =
      (2 * (quaternion_x * quaternion_y + quaternion_s * quaternion_z));

  *(p_dcmMatrix_out + 2) =
      (2 * (quaternion_x * quaternion_z - quaternion_s * quaternion_y));

  *(p_dcmMatrix_out + 3) =
      (2 * (quaternion_x * quaternion_y - quaternion_s * quaternion_z));

  *(p_dcmMatrix_out + 4) =
      (quaternion_s * quaternion_s + quaternion_x * quaternion_x -
       quaternion_y * quaternion_y - quaternion_z * quaternion_z);

  *(p_dcmMatrix_out + 5) =
      (2 * quaternion_y * quaternion_z + quaternion_s * quaternion_z);

  *(p_dcmMatrix_out + 6) =
      (2 * (quaternion_x * quaternion_z + quaternion_s * quaternion_y));

  *(p_dcmMatrix_out + 7) =
      (2 * (quaternion_y * quaternion_z - quaternion_s * quaternion_x));

  *(p_dcmMatrix_out + 8) =
      (quaternion_s * quaternion_s + quaternion_x * quaternion_x -
       quaternion_y * quaternion_y - quaternion_z * quaternion_z);

  return GCONST_TRUE;
}
