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
#include "GZero/GZero.h"

int JamSail_estimationEkfLoadVectors(double *p_stateEstimateVector_out,
                                     double *p_measurementEstimateVector_out,
                                     double *p_measurementSensorVector_out,
                                     JamSail_State  *p_jamSail_state_in,
                                     JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double  filteredAngularVelocity_Bod_rads[3];
  double  filteredMagneticField_Bod_nT[3];
  double  filteredMagneticFieldNorm_Bod[3];
  double  estimatedMagneticFieldNorm_Bod[3];
  double  filteredSunVectorNormRelToSen_Bod[3];
  uint8_t i;

  /* Clear variables */
  GZero(&(filteredAngularVelocity_Bod_rads[0]), double[3]);
  GZero(&(filteredMagneticField_Bod_nT[0]), double[3]);
  GZero(&(filteredMagneticFieldNorm_Bod[0]), double[3]);
  GZero(&(estimatedMagneticFieldNorm_Bod[0]), double[3]);
  GZero(&(filteredSunVectorNormRelToSen_Bod[0]), double[3]);

  /* Load the quaternion estimate into the state vector */
  for (i = 0; i < 4; i++)
  {
    *(p_stateEstimateVector_out + i) =
        (p_jamSail_state_in->quaternionEstimate_InertCenToBod[i]);
  }

  /* Load the angular velocity estimate into the state vector */
  for (i = 0; i < 3; i++)
  {
    *(p_stateEstimateVector_out + i + 4) =
        (p_jamSail_state_in->angularVelocityEstimate_Bod_rads[i]);
  }

  /* Find the unit vector of the estiamted magnetic field */
  GMath_findUnitVector(&(p_jamSail_state_in->magneticFieldEstimateNorm_Bod[0]),
                       &(estimatedMagneticFieldNorm_Bod[0]));

  /* Fill measurement estimate vector */
  for (i = 0; i < 3; i++)
  {
    *(p_measurementEstimateVector_out + i) =
        (p_jamSail_state_in->angularVelocityEstimate_Bod_rads[i]);
    *(p_measurementEstimateVector_out + i + 3) =
        estimatedMagneticFieldNorm_Bod[i];
    *(p_measurementEstimateVector_out + i + 6) =
        (p_jamSail_state_in->sunVectorEstimateNorm_Bod[i]);
  }

  /* Find the measured angular velocity in the body frame */
  GMath_quaternionPointRotation(
      &(filteredAngularVelocity_Bod_rads[0]),
      &(p_jamSail_state_in->gyro_state.filteredGyroVector_Sen_rads[0]),
      &(p_jamSail_params_in->gyro_params.sensorQuaternion_BodToSen[0]));

  /* Find the measured magnetic field in the body frame */
  GMath_quaternionPointRotation(
      &(filteredMagneticField_Bod_nT[0]),
      &(p_jamSail_state_in->magnetometer_state.filteredMagneticField_Sen_nT[0]),
      &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Find the unit vector of the measured magnetic field */
  GMath_findUnitVector(&(filteredMagneticField_Bod_nT[0]),
                       &(filteredMagneticFieldNorm_Bod[0]));

  /* Find the measured sun sensor vector in the body frame */
  GMath_quaternionPointRotation(
      &(filteredSunVectorNormRelToSen_Bod[0]),
      &(p_jamSail_state_in->sunSensor_state.filteredSunVector_Sen_m[0]),
      &(p_jamSail_params_in->sunSensor_params.sensorQuaternion_BodToSen[0]));

  /* Fill measurement sensor vector */
  for (i = 0; i < 3; i++)
  {
    *(p_measurementSensorVector_out + i) = filteredAngularVelocity_Bod_rads[i];
    *(p_measurementSensorVector_out + i + 3) = filteredMagneticFieldNorm_Bod[i];

    if (p_jamSail_state_in->sunSensor_state.isSensorReadingInvalid)
    {
      *(p_measurementSensorVector_out + i + 6) =
          p_jamSail_state_in->sunVectorEstimateNorm_Bod[i];
    }
    else
    {
      *(p_measurementSensorVector_out + i + 6) =
          filteredSunVectorNormRelToSen_Bod[i];
    }
  }

  return GCONST_TRUE;
}