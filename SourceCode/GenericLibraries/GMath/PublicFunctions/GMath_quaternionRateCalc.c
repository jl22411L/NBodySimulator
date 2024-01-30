/*
 *    @File:         GMath_quaternionRateCalc.c
 *
 *    @ Brief:       Finds the quaternion rate from the angular velocity vector
 *
 *    @ Date:        29/01/2024
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

int GMath_quaternionRateCalc(
    double *p_quaternionRate_out,
    double *p_quaternion_in,
    double *p_angularVelocity_in)
{
  /* Defining Local Variables */
  double angularVelocityX_rads;
  double angularVelocityY_rads;
  double angularVelocityZ_rads;
  double quaternionX;
  double quaternionY;
  double quaternionZ;
  double quaternionS;

  /* Declaring Local Variables */
  angularVelocityX_rads = *(p_angularVelocity_in + 0);
  angularVelocityY_rads = *(p_angularVelocity_in + 1);
  angularVelocityZ_rads = *(p_angularVelocity_in + 2);

  quaternionX = *(p_quaternion_in + 0);
  quaternionY = *(p_quaternion_in + 1);
  quaternionZ = *(p_quaternion_in + 2);
  quaternionS = *(p_quaternion_in + 3);

  *(p_quaternionRate_out + 0) = -quaternionY * angularVelocityX_rads -
                                quaternionZ * angularVelocityY_rads -
                                quaternionS * angularVelocityZ_rads;

  *(p_quaternionRate_out + 1) = quaternionX * angularVelocityX_rads +
                                quaternionZ * angularVelocityZ_rads -
                                quaternionS * angularVelocityY_rads;

  *(p_quaternionRate_out + 2) = quaternionX * angularVelocityY_rads -
                                quaternionY * angularVelocityZ_rads +
                                quaternionS * angularVelocityX_rads;

  *(p_quaternionRate_out + 3) = quaternionX * angularVelocityZ_rads +
                                quaternionY * angularVelocityY_rads -
                                quaternionZ * angularVelocityX_rads;

  return GCONST_TRUE;
}