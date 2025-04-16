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

int JamSail_fillObservationJacobian(JamSail_State *p_jamSail_state_out,
                                    int            isSunReadingInvalid_in)
{
  /* Declare local variables */
  double  rotationMatrix[3][3];
  double  vectorBuffer[3];
  double  magneticFieldNorm_Bod[3];
  uint8_t i;

  /* Clear local variables */
  GZero(&(rotationMatrix[0]), double[3][3]);
  GZero(&(vectorBuffer[0]), double[3]);

  /* Find unit vector of magnetic field */
  GMath_findUnitVector(
      &(p_jamSail_state_out->magneticFieldEstimateNorm_InertCen[0]),
      &(magneticFieldNorm_Bod[0]));

  /* Load the vectors due to the angular valocity */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_out->observationJacobian[i][i + 4]) = 1.0;
  }

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
               &(magneticFieldNorm_Bod[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[3][0]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[4][0]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[5][0]) = vectorBuffer[2];

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->sunVectorEstimateNorm_InertCen[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[6][0]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[7][0]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[8][0]) = vectorBuffer[2];

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
               &(magneticFieldNorm_Bod[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[3][1]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[4][1]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[5][1]) = vectorBuffer[2];

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->sunVectorEstimateNorm_InertCen[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[6][1]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[7][1]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[8][1]) = vectorBuffer[2];

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
               &(magneticFieldNorm_Bod[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[3][2]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[4][2]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[5][2]) = vectorBuffer[2];

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->sunVectorEstimateNorm_InertCen[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[6][2]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[7][2]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[8][2]) = vectorBuffer[2];

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
               &(magneticFieldNorm_Bod[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[3][3]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[4][3]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[5][3]) = vectorBuffer[2];

  GMath_matMul(&(rotationMatrix[0][0]),
               3,
               3,
               &(p_jamSail_state_out->sunVectorEstimateNorm_InertCen[0]),
               3,
               1,
               &(vectorBuffer[0]));

  (p_jamSail_state_out->observationJacobian[6][3]) = vectorBuffer[0];
  (p_jamSail_state_out->observationJacobian[7][3]) = vectorBuffer[1];
  (p_jamSail_state_out->observationJacobian[8][3]) = vectorBuffer[2];

  return GCONST_TRUE;
}