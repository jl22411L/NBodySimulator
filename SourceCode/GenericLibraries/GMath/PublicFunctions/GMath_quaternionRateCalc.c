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

int GMath_quaternionRateCalc(double *p_quaternionRate_out,
                             double *p_quaternion_in,
                             double *p_angularVelocity_in)
{
  /* Defining Local Variables */
  double angularVelocityX_rads;
  double angularVelocityY_rads;
  double angularVelocityZ_rads;
  double xQuaternionComponent;
  double yQuaternionComponent;
  double zQuaternionComponent;
  double sQuaternionComponent;

  /* Declaring Local Variables */
  angularVelocityX_rads = *(p_angularVelocity_in + 0);
  angularVelocityY_rads = *(p_angularVelocity_in + 1);
  angularVelocityZ_rads = *(p_angularVelocity_in + 2);

  xQuaternionComponent = *(p_quaternion_in + 0);
  yQuaternionComponent = *(p_quaternion_in + 1);
  zQuaternionComponent = *(p_quaternion_in + 2);
  sQuaternionComponent = *(p_quaternion_in + 3);

  /*!
   * Find the quaternion rate derivitive element wise.
   *
   * [ref:https://www.euclideanspace.com/physics/kinematics/angularvelocity/QuaternionDifferentiation2.pdf]
   */
  *(p_quaternionRate_out + 0) =
      0.5 * (sQuaternionComponent * angularVelocityX_rads +
             yQuaternionComponent * angularVelocityZ_rads -
             zQuaternionComponent * angularVelocityY_rads);

  *(p_quaternionRate_out + 1) =
      0.5 * (sQuaternionComponent * angularVelocityY_rads -
             xQuaternionComponent * angularVelocityZ_rads +
             zQuaternionComponent * angularVelocityX_rads);

  *(p_quaternionRate_out + 2) =
      0.5 * (sQuaternionComponent * angularVelocityZ_rads +
             xQuaternionComponent * angularVelocityY_rads -
             yQuaternionComponent * angularVelocityX_rads);

  *(p_quaternionRate_out + 3) =
      -0.5 * (xQuaternionComponent * angularVelocityX_rads +
              yQuaternionComponent * angularVelocityY_rads +
              zQuaternionComponent * angularVelocityZ_rads);

  return GCONST_TRUE;
}
