/*!
 *    @File:         Gyro_step.c
 *
 *    @Brief:        File which contains the function declaration for stepping
 *                   Gyro.
 *
 *    @Date:         05/02/2025
 *
 */

/* Function Includes */
#include "Gyro/PrivateFunctions/Gyro_PrivateFunctions.h"

/* Structure Include */
#include "Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Gyro_step(Gyro_Params *p_gyro_params_in,
              Gyro_State  *p_gyro_state_out,
              double      *p_angularVelocity_Fix_rads_in,
              double      *p_quaternion_FixToBod_in)
{
  /* Declare local variables */
  double quaternion_FixToSen[4];

  /* Clear variables */
  GZero(&(quaternion_FixToSen[0]), double[4]);

  /* Find quaternion from fix to sensor frame */
  GMath_quaternionMul(&(quaternion_FixToSen[0]),
                      &(p_gyro_params_in->sensorQuaternion_BodToSen[0]),
                      p_quaternion_FixToBod_in);

  /* Find angular velocity in sensor frame */
  GMath_quaternionFrameRotation(&(p_gyro_state_out->trueGyroVector_Sen_rads[0]),
                                p_angularVelocity_Fix_rads_in,
                                &(quaternion_FixToSen[0]));

  /* Find noise component of Gyro */
  // TODO

  /* Find measurement component of Gyro */
  p_gyro_state_out->measuredGyroVector_Sen_rads[0] =
      p_gyro_state_out->trueGyroVector_Sen_rads[0] +
      p_gyro_state_out->noiseGyroVector_Sen_rads[0];
  p_gyro_state_out->measuredGyroVector_Sen_rads[1] =
      p_gyro_state_out->trueGyroVector_Sen_rads[1] +
      p_gyro_state_out->noiseGyroVector_Sen_rads[1];
  p_gyro_state_out->measuredGyroVector_Sen_rads[2] =
      p_gyro_state_out->trueGyroVector_Sen_rads[2] +
      p_gyro_state_out->noiseGyroVector_Sen_rads[2];

  /* Archive data */
  Gyro_archiveData(p_gyro_state_out);

  return GCONST_TRUE;
}