/*
 *    @File:         GMath_quaternionFrameRotation.c
 *
 *    @ Brief:       Rotate a point wihtin the frame it is represented in,
 *                   using a quaternion
 *
 *    @ Date:        14/05/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "GMath/PublicFunctions/GMath_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
#include "GMath/ConstantDefs/GMath_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GMath_quaternionFrameRotation(double *p_rotatedVector_out,
                                  double *p_vectorToRotate_in,
                                  double *p_quaternion_in)
{
  /* Declaring Local Variables Local variables */
  double  quaternionBuffer[4];
  double  quaternionConjugate[4];
  double  inputPureQuaternion[4];
  double  outputPureQuaternion[4];
  double  xQuaternionComponent;
  double  yQuaternionComponent;
  double  zQuaternionComponent;
  double  sQuaternionComponent;
  double  outputUnitQuaternion[4];
  uint8_t i;

  /* Clear Buffer */
  GZero(&quaternionBuffer[0], double[4]);
  GZero(&quaternionConjugate[0], double[4]);
  GZero(&inputPureQuaternion[0], double[4]);
  GZero(&outputPureQuaternion[0], double[4]);
  GZero(&outputUnitQuaternion[0], double[4]);

  /* Turn the vector into a pure quaternion */
  for (i = 0; i < 3; i++)
  {
    inputPureQuaternion[i] = *(p_vectorToRotate_in + i);
  }

  /* Find the conjugate of the quaternion */
  GMath_quaternionConjugate(&quaternionConjugate[0], p_quaternion_in);

  /*
   * Note: The rotation is defined as;
   *              outputVector = quaternionConjugate * inputVector * quaternion
   *
   *        Where, the * represent quaternion multiplication and not normal
   *        multiplication.
   */

  /* Find Quaternion Buffer for itermediate multiplication */
  GMath_quaternionMul(&quaternionBuffer[0],
                      &quaternionConjugate[0],
                      &inputPureQuaternion[0]);

  /* Find output pure quaternion */
  GMath_quaternionMul(&outputPureQuaternion[0],
                      &quaternionBuffer[0],
                      p_quaternion_in);

  /* Find the unit quaternion of the output */
  GMath_findUnitQuaternion(&(outputPureQuaternion[0]),
                           &(outputUnitQuaternion[0]));

  /* Check that it is q pure quaternion */
  if (outputUnitQuaternion[3] > GMATH_QUATERNION_ZERO_TOLERANCE)
  {
    GError("Resulting quatenrion is not a pure quaternion. ",
           "outputPureQuaternion = [%lf, %lf, %lf, %lf]",
           outputPureQuaternion[0],
           outputPureQuaternion[1],
           outputPureQuaternion[2],
           outputPureQuaternion[3]);
  }

  /* Extract the gibs vector from the output quaternion */
  for (i = 0; i < 3; i++)
  {
    *(p_rotatedVector_out + i) = outputPureQuaternion[i];
  }

  return GCONST_TRUE;
}
