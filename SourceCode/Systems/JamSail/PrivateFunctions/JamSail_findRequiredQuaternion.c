/*
 *    @File:         JamSail_findRequiredQuaternion.c
 *
 *    @Brief:        Funnction definition for finding the required quaternion
 *
 *    @Date:         07/04/2025
 *
 */

#include <math.h>
#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int JamSail_findRequiredQuaternion(
    JamSail_State  *p_jamSail_state_in,
    JamSail_Params *p_jamSail_params_in,
    double         *p_requiredQuaternion_InertCenToBod_out)
{
  /* Declare local variables */
  double  rotationAxis[3];
  double  pointingAxis_Fix[3];
  double  pointingDirection_Fix[3];
  double  rotationAngle_rad;
  double  dotProduct;
  uint8_t i;

  /* Clear variables */
  GZero(&(rotationAxis), double[3]);
  GZero(&(pointingAxis_Fix), double[3]);
  GZero(&(pointingDirection_Fix), double[3]);

  /*!
   * Set pointing axis
   *(This rotated into the body frame shall be what you want pointing)
   */
  pointingAxis_Fix[0] = 1.0;

  /*!
   * Set pointing direction.
   * (This is the direction that the pointing axis will be rotated towards)
   */
  for (i = 0; i < 3; i++)
  {
    pointingDirection_Fix[i] =
        -(p_jamSail_state_in->positionEstimate_InertCen_m[i]);
  }

  /* Make pointing direction a unit vector */
  GMath_findUnitVector(&(pointingDirection_Fix[0]),
                       &(pointingDirection_Fix[0]));

  /* Find first rotation axis */
  GMath_crossProduct(&(pointingAxis_Fix[0]),
                     &(pointingDirection_Fix[0]),
                     &(rotationAxis[0]));

  /* Find the dot product of pointing direction and pointing axis */
  dotProduct = 0.0;
  for (i = 0; i < 3; i++)
  {
    dotProduct += pointingAxis_Fix[i] * pointingDirection_Fix[i];
  }

  /* Find the rotation angle */
  rotationAngle_rad = acos(dotProduct);

  /* Find required quaternion */
  p_requiredQuaternion_InertCenToBod_out[0] =
      sin(rotationAngle_rad / 2) * rotationAxis[0];
  p_requiredQuaternion_InertCenToBod_out[1] =
      sin(rotationAngle_rad / 2) * rotationAxis[1];
  p_requiredQuaternion_InertCenToBod_out[2] =
      sin(rotationAngle_rad / 2) * rotationAxis[2];
  p_requiredQuaternion_InertCenToBod_out[3] = cos(rotationAngle_rad / 2);

  return GCONST_TRUE;
}