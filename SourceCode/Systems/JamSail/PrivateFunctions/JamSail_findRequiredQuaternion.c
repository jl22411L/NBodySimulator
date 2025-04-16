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
  double  pointingAxis_InertCen[3];
  double  pointingDirection_InertCen[3];
  double  intermediateRequiredQuaternion_InertCenToBod[4];
  double  intermediateRequiredQuaternion2_InertCenToBod[4];
  double  sunVector_Bod[3];
  double  crossProductMagnitude;
  double  pointingAxisMagnitude;
  double  pointingDirectionMagnitude;
  double  rotationAngle_rad;
  double  dotProduct;
  uint8_t i;

  /* Clear variables */
  GZero(&(rotationAxis), double[3]);
  GZero(&(pointingAxis_InertCen), double[3]);
  GZero(&(pointingDirection_InertCen), double[3]);
  GZero(&(intermediateRequiredQuaternion_InertCenToBod), double[4]);
  GZero(&(intermediateRequiredQuaternion2_InertCenToBod), double[4]);
  GZero(&(sunVector_Bod), double[3]);

  /*!
   * Set pointing axis
   * (This rotated into the body frame shall be what you want pointing)
   */
  pointingAxis_InertCen[0] = 1.0;

  /*!
   * Set pointing direction.
   * (This is the direction that the pointing axis will be rotated towards)
   */
  for (i = 0; i < 3; i++)
  {
    pointingDirection_InertCen[i] =
        -(p_jamSail_state_in->positionEstimate_InertCen_m[i]);
  }

  /* Make pointing direction a unit vector */
  GMath_findUnitVector(&(pointingDirection_InertCen[0]),
                       &(pointingDirection_InertCen[0]));

  /* Find first rotation axis */
  GMath_crossProduct(&(pointingAxis_InertCen[0]),
                     &(pointingDirection_InertCen[0]),
                     &(rotationAxis[0]));

  /* Find magnitude of cross product */
  GMath_vectorMag(&crossProductMagnitude, &rotationAxis[0], 3);

  /* Find the dot product of pointing direction and pointing axis */
  dotProduct = 0.0;
  for (i = 0; i < 3; i++)
  {
    dotProduct += pointingAxis_InertCen[i] * pointingDirection_InertCen[i];
  }

  GMath_vectorMag(&pointingAxisMagnitude, &(pointingAxis_InertCen[0]), 3);
  GMath_vectorMag(&pointingDirectionMagnitude,
                  &(pointingDirection_InertCen[0]),
                  3);

  /* Find the rotation angle */
  rotationAngle_rad =
      acos(dotProduct / pointingAxisMagnitude / pointingDirectionMagnitude);

  /* Find required quaternion */
  intermediateRequiredQuaternion_InertCenToBod[0] =
      sin(rotationAngle_rad / 2) * rotationAxis[0] / crossProductMagnitude;
  intermediateRequiredQuaternion_InertCenToBod[1] =
      sin(rotationAngle_rad / 2) * rotationAxis[1] / crossProductMagnitude;
  intermediateRequiredQuaternion_InertCenToBod[2] =
      sin(rotationAngle_rad / 2) * rotationAxis[2] / crossProductMagnitude;
  intermediateRequiredQuaternion_InertCenToBod[3] = cos(rotationAngle_rad / 2);

  /* Make sure quaternion is unique */
  GMath_findUnitQuaternion(&(intermediateRequiredQuaternion_InertCenToBod[0]),
                           &(intermediateRequiredQuaternion_InertCenToBod[0]));

  /* Find the rotating axis */
  rotationAxis[0] = 1.0;
  rotationAxis[1] = 0.0;
  rotationAxis[2] = 0.0;

  /* If sun sensor is detected, find rotation angle using sun sensor */
  if (p_jamSail_state_in->sunSensor_state.isSensorReadingInvalid ==
      GCONST_FALSE)
  {
    /* FInd sun vector in body frame */
    GMath_quaternionPointRotation(
        &(sunVector_Bod[0]),
        &(p_jamSail_state_in->sunSensor_state.filteredSunVector_Sen_m[0]),
        &(p_jamSail_params_in->sunSensor_params.sensorQuaternion_BodToSen[0]));

    /* Find rotation angle */
    rotationAngle_rad = atan2(-sunVector_Bod[1], sunVector_Bod[2]);
  }
  /* Else, use estiamte of sun position */
  else
  {
    /* Find rotation angle */
    rotationAngle_rad = atan2(-p_jamSail_state_in->sunVectorEstimateNorm_Bod[1],
                              p_jamSail_state_in->sunVectorEstimateNorm_Bod[2]);
  }

  /* Find required quaternion */
  intermediateRequiredQuaternion2_InertCenToBod[0] =
      sin(rotationAngle_rad / 2) * rotationAxis[0];
  intermediateRequiredQuaternion2_InertCenToBod[1] =
      sin(rotationAngle_rad / 2) * rotationAxis[1];
  intermediateRequiredQuaternion2_InertCenToBod[2] =
      sin(rotationAngle_rad / 2) * rotationAxis[2];
  intermediateRequiredQuaternion2_InertCenToBod[3] = cos(rotationAngle_rad / 2);

  /* Find resultant quaternion */
  GMath_quaternionMul(
      &(p_jamSail_state_in->requiredQuaternion_InertCenToBod[0]),
      &(intermediateRequiredQuaternion2_InertCenToBod[0]),
      &(intermediateRequiredQuaternion_InertCenToBod[0]));

  /* Stabalise requiered quaternion */
  GMath_findUnitQuaternion(
      &(p_jamSail_state_in->requiredQuaternion_InertCenToBod[0]),
      &(p_jamSail_state_in->requiredQuaternion_InertCenToBod[0]));

  return GCONST_TRUE;
}