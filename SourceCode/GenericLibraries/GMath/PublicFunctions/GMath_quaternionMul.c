/*
 *    @File:         GMath_quaternionMul.c
 *
 *    @Brief:        Performas quaternion multiplication on two quaternion
 *                   vectors.
 *
 *    @Date:         15/05/2024
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

int GMath_quaternionMul(
    double *p_quaternionP_in,
    double *p_quaternionQ_in,
    double *p_outputQuaternion_out)
{
  /* Define local variables */
  double xQuaternionPComponent;
  double yQuaternionPComponent;
  double zQuaternionPComponent;
  double sQuaternionPComponent;
  double xQuaternionQComponent;
  double yQuaternionQComponent;
  double zQuaternionQComponent;
  double sQuaternionQComponent;

  /* Decompose quaternion P */
  xQuaternionPComponent = *(p_quaternionP_in + 0);
  yQuaternionPComponent = *(p_quaternionP_in + 1);
  zQuaternionPComponent = *(p_quaternionP_in + 2);
  sQuaternionPComponent = *(p_quaternionP_in + 3);

  /* Decompose quaternion Q */
  xQuaternionQComponent = *(p_quaternionQ_in + 0);
  yQuaternionQComponent = *(p_quaternionQ_in + 1);
  zQuaternionQComponent = *(p_quaternionQ_in + 2);
  sQuaternionQComponent = *(p_quaternionQ_in + 3);

  /* Find result of output quaternion */
  *(p_outputQuaternion_out + 0) =
      xQuaternionPComponent * sQuaternionQComponent +
      yQuaternionPComponent * zQuaternionQComponent -
      zQuaternionPComponent * yQuaternionQComponent +
      sQuaternionPComponent * xQuaternionQComponent;

  *(p_outputQuaternion_out + 1) =
      -xQuaternionPComponent * zQuaternionQComponent +
      yQuaternionPComponent * sQuaternionQComponent +
      zQuaternionPComponent * xQuaternionQComponent +
      sQuaternionPComponent * yQuaternionQComponent;

  *(p_outputQuaternion_out + 2) =
      xQuaternionPComponent * yQuaternionQComponent -
      yQuaternionPComponent * xQuaternionQComponent +
      zQuaternionPComponent * sQuaternionQComponent +
      sQuaternionPComponent * zQuaternionQComponent;

  *(p_outputQuaternion_out + 3) =
      -xQuaternionPComponent * xQuaternionQComponent -
      yQuaternionPComponent * yQuaternionQComponent -
      zQuaternionPComponent * zQuaternionQComponent +
      sQuaternionPComponent * sQuaternionQComponent;

  return GCONST_TRUE;
}
