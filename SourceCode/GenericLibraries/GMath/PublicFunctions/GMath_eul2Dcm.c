/*
 *    @File:         GMath_eul2Dcm.c
 *
 *    @Brief:        GMath fucntion which converts euler angles to a dcm
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

int GMath_eul2Dcm(double *p_eulerAngleVector_rad_in, double *p_dcmMatrix_out)
{
  /* Declare local variables */
  double roll_rad;
  double pitch_rad;
  double yaw_rad;

  /* Decompose the euler vector */
  roll_rad  = *(p_eulerAngleVector_rad_in + 0);
  pitch_rad = *(p_eulerAngleVector_rad_in + 1);
  yaw_rad   = *(p_eulerAngleVector_rad_in + 2);

  /* Find components of DCM */
  *(p_dcmMatrix_out + 0) = (cos(yaw_rad) * cos(pitch_rad));

  *(p_dcmMatrix_out + 1) = (sin(yaw_rad) * cos(pitch_rad));

  *(p_dcmMatrix_out + 2) = (-sin(pitch_rad));

  *(p_dcmMatrix_out + 3) =
      (cos(yaw_rad) * sin(pitch_rad) * sin(roll_rad) -
       sin(yaw_rad) * sin(roll_rad));

  *(p_dcmMatrix_out + 4) =
      (sin(yaw_rad) * sin(pitch_rad) * sin(roll_rad) +
       cos(yaw_rad) * cos(roll_rad));

  *(p_dcmMatrix_out + 5) = (cos(pitch_rad) * sin(roll_rad));

  *(p_dcmMatrix_out + 6) =
      (cos(yaw_rad) * sin(pitch_rad) * cos(roll_rad) +
       sin(yaw_rad) * sin(roll_rad));

  *(p_dcmMatrix_out + 7) =
      (sin(yaw_rad) * sin(pitch_rad) * cos(roll_rad) -
       cos(yaw_rad) * sin(roll_rad));

  *(p_dcmMatrix_out + 8) = (cos(pitch_rad) * cos(roll_rad));

  return GCONST_TRUE;
}
