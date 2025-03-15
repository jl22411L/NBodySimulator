/*!
 *    @File:         JamSail_fillObservationJacobian.c
 *
 *    @Brief:        Private function which will fill the obersvation jacobian.
 *
 *    @Date:         09/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int JamSail_fillObservationJacobian(JamSail_State *p_jamSail_state_out)
{
  /* Declare local variables */
  double  rotationMatrix[3][3];
  double  vectorBuffer[3];
  uint8_t i;

  rotationMatrix[0][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[0][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[0][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[1][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[1][1] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[1][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[2][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[2][1] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[2][2] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->magneticFieldEstimateNorm_InertCen_nT[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[0][0]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[1][0]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[2][0]) = vectorBuffer[2];

  rotationMatrix[0][0] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[0][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[0][2] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[1][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[1][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[1][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[2][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[2][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[2][2] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->magneticFieldEstimateNorm_InertCen_nT[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[0][1]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[1][1]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[2][1]) = vectorBuffer[2];

  rotationMatrix[0][0] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[0][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[0][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[1][0] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[1][1] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[1][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[2][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[2][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[2][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->magneticFieldEstimateNorm_InertCen_nT[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[0][2]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[1][2]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[2][2]) = vectorBuffer[2];

  rotationMatrix[0][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[0][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[0][2] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[1][0] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  rotationMatrix[1][1] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  rotationMatrix[1][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[2][0] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  rotationMatrix[2][1] =
      -2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  rotationMatrix[2][2] =
      2 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->magneticFieldEstimateNorm_InertCen_nT[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[0][3]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[1][3]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[2][3]) = vectorBuffer[2];

  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_out->observationJacobian[i + 3][i + 4]) = 1.0;
  }

  return GCONST_TRUE;
}