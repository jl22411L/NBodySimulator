/*
 *    @File:         JamSail_sunTrackingControl.c
 *
 *    @Brief:        Funciton definition for snu trakcking control.
 *
 *    @Date:         13/04/2025
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

int JamSail_sunTrackingControl(JamSail_State  *p_jamSail_state_inout,
                               JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double        sunVector_Bod[3];
  double        controlDipole_Bod_NmpT[3];
  double        controlDipole_Sen_NmpT[3];
  double        measuredMagneticField_Bod_nT[3];
  double        angularMomentum_Bod_radkgm2[3];
  double        crossRotationalMoments_Bod_Nm[3];
  double        magneticFieldMagnitude_nT;
  double        xError_rad;
  double        yError_rad;
  double        derivitiveX_radps;
  double        derivitiveY_radps;
  static double previousX_rad;
  static double previousY_rad;
  uint8_t       i;

  /* Clear local variables */
  GZero(&(sunVector_Bod[0]), double[3]);
  GZero(&(controlDipole_Bod_NmpT[0]), double[3]);
  GZero(&(controlDipole_Sen_NmpT[0]), double[3]);
  GZero(&(measuredMagneticField_Bod_nT[0]), double[3]);
  GZero(&(angularMomentum_Bod_radkgm2[0]), double[3]);
  GZero(&(crossRotationalMoments_Bod_Nm[0]), double[3]);

  /* Find the angular momentum of the rigid body */
  GMath_matMul(&(p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
                     .inertiaMatrix_Bod_kgm2[0][0]),
               3,
               3,
               &(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]),
               3,
               1,
               &angularMomentum_Bod_radkgm2[0]);

  /* Find the cross rotational inertia moements */
  GMath_crossProduct(
      &(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]),
      &(angularMomentum_Bod_radkgm2[0]),
      &(crossRotationalMoments_Bod_Nm[0]));

  /* Find the sun vector in the body frame */
  GMath_quaternionPointRotation(
      &(sunVector_Bod[0]),
      &(p_jamSail_state_inout->sunSensor_state.filteredSunVector_Sen_m[0]),
      &(p_jamSail_params_in->sunSensor_params.sensorQuaternion_BodToSen[0]));

  /* Find the angle of rotation */
  xError_rad = atan2(-sunVector_Bod[1], sunVector_Bod[2]);
  yError_rad = atan2(sunVector_Bod[0], sunVector_Bod[2]);

  /* Find derivitive of tracking angle */
  if (p_jamSail_state_inout->trackingTimeOfSun_s == 0.0)
  {
    derivitiveX_radps = 0.0;
    derivitiveY_radps = 0.0;
  }
  else
  {
    derivitiveX_radps = (xError_rad - previousX_rad) / 0.01;
    derivitiveY_radps = (yError_rad - previousY_rad) / 0.01;
  }

  previousX_rad = xError_rad;
  previousY_rad = yError_rad;

  (p_jamSail_state_inout->controlTorque_Bod_Nm[0]) =
      (p_jamSail_params_in->nominalProportionalCoefficient[0]) * xError_rad +
      (p_jamSail_params_in->detumblingProportionalCoefficient[0]) *
          (derivitiveX_radps) -
      (p_jamSail_params_in->detumblingProportionalCoefficient[0]) *
          (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]) +
      crossRotationalMoments_Bod_Nm[0];

  (p_jamSail_state_inout->controlTorque_Bod_Nm[1]) =
      (p_jamSail_params_in->nominalProportionalCoefficient[1]) * yError_rad +
      (p_jamSail_params_in->detumblingProportionalCoefficient[1]) *
          (derivitiveY_radps) -
      (p_jamSail_params_in->detumblingProportionalCoefficient[1]) *
          (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]) +
      crossRotationalMoments_Bod_Nm[1];

  (p_jamSail_state_inout->controlTorque_Bod_Nm[2]) =
      -(p_jamSail_params_in->nominalDerivitiveCoefficient[2]) *
          (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]) +
      crossRotationalMoments_Bod_Nm[2];

  return GCONST_TRUE;
}