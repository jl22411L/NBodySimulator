/*
 *    @File:         JamSail_nominalAlgorithm.c
 *
 *    @Brief:        Function definition for nominal control of JamSail
 *
 *    @Date:         07/04/2025
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

int JamSail_nominalAlgorithm(JamSail_State  *p_jamSail_state_inout,
                             JamSail_Params *p_jamSail_params_in,
                             double *p_requiredQuaternion_InertCenToBod_in)
{
  /* Declare local variables */
  double  angularVelocitiesError_rads[3];
  double  controlDipole_Bod_NmpT[3];
  double  controlDipole_Sen_NmpT[3];
  double  measuredMagneticField_Bod_nT[3];
  double  errorQuaternion_InertCenToBod[4];
  double  magneticFieldMagnitude_nT;
  uint8_t i;

  /* Clear local variables */
  GZero(&(angularVelocitiesError_rads[0]), double[3]);
  GZero(&(controlDipole_Bod_NmpT[0]), double[3]);
  GZero(&(controlDipole_Sen_NmpT[0]), double[3]);
  GZero(&(measuredMagneticField_Bod_nT[0]), double[3]);
  GZero(&(errorQuaternion_InertCenToBod[0]), double[4]);

  /* ------------------------------------------------------------------------ *
   * Error Vector Calcaultions
   * ------------------------------------------------------------------------ */

  /* Find error in angular velocity */
  for (i = 0; i < 3; i++)
  {
    angularVelocitiesError_rads[i] =
        0.0 - (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]);
  }

  /* Find the error quaternion */
  errorQuaternion_InertCenToBod[0] =
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  errorQuaternion_InertCenToBod[1] =
      -(p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  errorQuaternion_InertCenToBod[2] =
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  errorQuaternion_InertCenToBod[3] =
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  /* Find control torque */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_inout->controlTorque_Bod_Nm[i]) =
        (p_jamSail_params_in->nominalProportionalCoefficient[i]) *
            errorQuaternion_InertCenToBod[i] +
        (p_jamSail_params_in->nominalDerivitiveCoefficient[i]) *
            angularVelocitiesError_rads[i];
  }

  /* Find magnetic field in the body frame */
  GMath_quaternionPointRotation(
      &(measuredMagneticField_Bod_nT[0]),
      &(p_jamSail_state_inout->magnetometer_state
            .measuredMagneticField_Sen_nT[0]),
      &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Find magnetic field magnitude */
  GMath_vectorMag(&magneticFieldMagnitude_nT,
                  &(measuredMagneticField_Bod_nT[0]),
                  3);

  /* Find cross product of magnetic field and control torques */
  GMath_crossProduct(&(measuredMagneticField_Bod_nT[0]),
                     &(p_jamSail_state_inout->controlTorque_Bod_Nm[0]),
                     &controlDipole_Bod_NmpT[0]);

  /* Find control dipoles */
  for (i = 0; i < 3; i++)
  {
    /*!
     * Scale the unit of the current value in the control dipole.
     *(Not included in cross product)
     */
    controlDipole_Bod_NmpT[i] *= GCONST_NM_TOLERANCE;

    /* Divide by the magnitude of the magnetic field squared */
    controlDipole_Bod_NmpT[i] /=
        (magneticFieldMagnitude_nT * GCONST_NM_TOLERANCE) *
        (magneticFieldMagnitude_nT * GCONST_NM_TOLERANCE);
  }

  /* Find the control dipole in the sensor frame */
  GMath_quaternionFrameRotation(
      &(controlDipole_Sen_NmpT[0]),
      &(controlDipole_Bod_NmpT[0]),
      &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  /* Find control currents */
  for (i = 0; i < 3; i++)
  {
    /* Find the ideal control current */
    (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
        controlDipole_Sen_NmpT[i] /
        (p_jamSail_params_in->magnetorquer_params.coilArea_Sen_m2[i] *
         p_jamSail_params_in->magnetorquer_params.coilTurns_Sen[i]);

    /* Flatten ideal current to be within peak tolerances */
    if ((p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) >
        (p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]))
    {
      /* Ideal current is greater in positive direction */
      (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
          (p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]);
    }
    else if ((p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) <
             (p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]))
    {
      /* Ideal current is greater in negative direction */
      (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
          -(p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]);
    }
  }

  return GCONST_TRUE;
}