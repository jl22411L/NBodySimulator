/*!
 *    @File:         JamSail_estimationEkf_loadStateVector.c
 *
 *    @Brief:        Private function which will load the state estimate vector
 *                   into the EKF for when JamSail is estimating its attitude.
 *
 *    @Date:         08/03/2025
 *
 */

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

int JamSail_estimationEkfLoadVectors(double *p_stateEstimateVector_out,
                                     double *p_measurementEstimateVector_out,
                                     double *p_measurementSensorVector_out,
                                     JamSail_State  *p_jamSail_state_in,
                                     JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double  filteredAngularVelocity_Bod_rads[3];
  double  filteredMagneticFieldNorm_Bod_nT[3];
  uint8_t i;

  /* Load the quaternion estimate into the state vector */
  for (i = 0; i < 4; i++)
  {
    *(p_stateEstimateVector_out + i) =
        (p_jamSail_state_in->quaternionEstimate_InertCenToBod[i]);
  }

  /* Load the angular velocity estimate into the state vector */
  for (i = 0; i < 3; i++)
  {
    *(p_stateEstimateVector_out + i) =
        (p_jamSail_state_in->angularVelocityEstimate_Bod_rads[i]);
  }

  /* Fill measurement estimate vector */
  for (i = 0; i < 3; i++)
  {
    *(p_measurementEstimateVector_out + i) =
        (p_jamSail_state_in->magneticFieldEstimateNorm_Bod_nT[i]);
    *(p_measurementEstimateVector_out + i + 3) =
        (p_jamSail_state_in->angularVelocityEstimate_Bod_rads[i]);
  }

  /* Find the measured angular velocity in the body frame */
  GMath_quaternionPointRotation(
      &(filteredAngularVelocity_Bod_rads[0]),
      &(p_jamSail_state_in->gyro_state.filteredGyroVector_Sen_rads[0]),
      &(p_jamSail_params_in->gyro_params.sensorQuaternion_BodToSen[0]));

  /* Find the measured magnetic field in the body frame */
  GMath_quaternionPointRotation(
      &(filteredMagneticFieldNorm_Bod_nT[0]),
      &(p_jamSail_state_in->magnetometer_state.measuredMagneticField_Sen_nT[0]),
      &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Find norm of magnetic field */
  GMath_vectorNorm(&(filteredMagneticFieldNorm_Bod_nT[0]),
                   &(filteredMagneticFieldNorm_Bod_nT[0]),
                   3);

  /* Fill measurement sensor vector */
  for (i = 0; i < 3; i++)
  {
    *(p_measurementSensorVector_out + i) = filteredMagneticFieldNorm_Bod_nT[i];
    *(p_measurementSensorVector_out + i + 3) =
        filteredAngularVelocity_Bod_rads[i];
  }

  return GCONST_TRUE;
}