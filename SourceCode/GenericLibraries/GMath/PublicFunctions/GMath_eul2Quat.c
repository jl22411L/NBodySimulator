/*
 *    @File:         GMath_eul2Quat.c
 *
 *    @Brief:
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

int GMath_eul2Quat(
    double *p_eulerAnglevector_rad_in,
    double *p_quaternionVector_out)
{
  /* Declare Local Variables */
  double roll_rad;
  double pitch_rad;
  double yaw_rad;

  /* Extract Euler angles from input vector */
  roll_rad  = *(p_eulerAnglevector_rad_in + 0);
  pitch_rad = *(p_eulerAnglevector_rad_in + 1);
  yaw_rad   = *(p_eulerAnglevector_rad_in + 2);

  /* Find quaternion components */
  *(p_quaternionVector_out + 0) =
      cos(yaw_rad / 2) * cos(pitch_rad / 2) * sin(roll_rad / 2) -
      sin(yaw_rad / 2) * sin(pitch_rad / 2) * cos(roll_rad / 2);

  *(p_quaternionVector_out + 1) =
      cos(yaw_rad / 2) * sin(pitch_rad / 2) * cos(roll_rad / 2) +
      sin(yaw_rad / 2) * cos(pitch_rad / 2) * sin(roll_rad / 2);

  *(p_quaternionVector_out + 2) =
      sin(yaw_rad / 2) * cos(pitch_rad / 2) * cos(roll_rad / 2) -
      cos(yaw_rad / 2) * sin(pitch_rad / 2) * sin(roll_rad / 2);

  *(p_quaternionVector_out + 3) =
      cos(yaw_rad / 2) * cos(pitch_rad / 2) * cos(roll_rad / 2) +
      sin(yaw_rad / 2) * sin(pitch_rad / 2) * sin(roll_rad / 2);

  return GCONST_TRUE;
}
