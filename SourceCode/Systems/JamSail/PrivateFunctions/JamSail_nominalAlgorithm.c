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
  double  controlDipole_Bod_NmpT[3];
  double  controlDipole_Sen_NmpT[3];
  double  measuredMagneticField_Bod_T[3];
  double  angularMomentum_radkgm2_Bod[3];
  double  crossRotationalMoments_Nm_Bod[3];
  double  magneticFieldMagnitude_T;
  uint8_t i;

  /* Clear local variables */
  GZero(&(controlDipole_Bod_NmpT[0]), double[3]);
  GZero(&(controlDipole_Sen_NmpT[0]), double[3]);
  GZero(&(measuredMagneticField_Bod_T[0]), double[3]);
  GZero(&(angularMomentum_radkgm2_Bod[0]), double[3]);
  GZero(&(crossRotationalMoments_Nm_Bod[0]), double[3]);

  /* ------------------------------------------------------------------------ *
   * Error Vector Calcaultions
   * ------------------------------------------------------------------------ */

  double quaternion_InertCenToBod[4];
  double quaternion_InertCenToFix[4];
  GZero(&(quaternion_InertCenToBod[0]), double[4]);
  GZero(&(quaternion_InertCenToFix[0]), double[4]);

  GMath_quaternionConjugate(
      &(quaternion_InertCenToFix[0]),
      &(p_jamSail_params_in->quaternion_FixToInertCen[0]));

  GMath_quaternionMul(&(quaternion_InertCenToBod[0]),
                      &(quaternion_InertCenToFix[0]),
                      &(p_jamSail_state_inout->p_satelliteBody_state
                            ->rigidBody_state.quaternion_FixToBody[0]));

  /* Find error quaternion */
  p_jamSail_state_inout->errorQuaternion_InertCenToBod[0] =
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (quaternion_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (quaternion_InertCenToBod[1]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (quaternion_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (quaternion_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[1] =
      -(p_requiredQuaternion_InertCenToBod_in[2]) *
          (quaternion_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (quaternion_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (quaternion_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (quaternion_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[2] =
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (quaternion_InertCenToBod[0]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (quaternion_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (quaternion_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (quaternion_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[3] =
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (quaternion_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (quaternion_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (quaternion_InertCenToBod[2]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (quaternion_InertCenToBod[3]);

  /* Find the unit vector of the error quaternion */
  GMath_findUnitQuaternion(
      &(p_jamSail_state_inout->errorQuaternion_InertCenToBod[0]),
      &(p_jamSail_state_inout->errorQuaternion_InertCenToBod[0]));

  /* Find the angular momentum of the rigid body */
  GMath_matMul(&(p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
                     .inertiaMatrix_Bod_kgm2[0][0]),
               3,
               3,
               &p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0],
               3,
               1,
               &angularMomentum_radkgm2_Bod[0]);

  /* Find the cross rotational inertia moements */
  GMath_crossProduct(
      &p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0],
      &angularMomentum_radkgm2_Bod[0],
      &crossRotationalMoments_Nm_Bod[0]);

  /* Find control torque */
  for (i = 0; i < 3; i++)
  {
    (p_jamSail_state_inout->controlTorque_Bod_Nm[i]) =
        -(p_jamSail_params_in->nominalProportionalCoefficient[i]) *
            (p_jamSail_state_inout->errorQuaternion_InertCenToBod[i]) -
        (p_jamSail_params_in->nominalDerivitiveCoefficient[i]) *
            (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[i]) +
        crossRotationalMoments_Nm_Bod[i];
  }

  for (i = 0; i < 3; i++)
  {
    if (p_jamSail_state_inout->controlTorque_Bod_Nm[i] > 0.001)
    {
      p_jamSail_state_inout->controlTorque_Bod_Nm[i] = 0.001;
    }
    else if (p_jamSail_state_inout->controlTorque_Bod_Nm[i] < -0.001)
    {
      p_jamSail_state_inout->controlTorque_Bod_Nm[i] = -0.001;
    }
  }

  //   /* Find magnetic field in the body frame */
  //   GMath_quaternionPointRotation(
  //       &(measuredMagneticField_Bod_T[0]),
  //       &(p_jamSail_state_inout->magnetometer_state
  //             .measuredMagneticField_Sen_nT[0]),
  //       &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  //   /* Scale the measured magnetic field into Tesla */
  //   for (i = 0; i < 3; i++)
  //   {
  //     measuredMagneticField_Bod_T[i] *= GCONST_NM_TOLERANCE;
  //   }

  //   /* Find magnetic field magnitude */
  //   GMath_vectorMag(&magneticFieldMagnitude_T,
  //                   &(measuredMagneticField_Bod_T[0]),
  //                   3);

  //   /* Find cross product of magnetic field and control torques */
  //   GMath_crossProduct(&(measuredMagneticField_Bod_T[0]),
  //                      &(p_jamSail_state_inout->controlTorque_Bod_Nm[0]),
  //                      &controlDipole_Bod_NmpT[0]);

  //   /* Find control dipoles */
  //   for (i = 0; i < 3; i++)
  //   {
  //     /* Divide by the magnitude of the magnetic field squared */
  //     controlDipole_Bod_NmpT[i] /=
  //         (magneticFieldMagnitude_T * magneticFieldMagnitude_T);
  //   }

  //   /* Find the control dipole in the sensor frame */
  //   GMath_quaternionFrameRotation(
  //       &(controlDipole_Sen_NmpT[0]),
  //       &(controlDipole_Bod_NmpT[0]),
  //       &(p_jamSail_params_in->magnetometer_params.sensorQuaternion_BodToSen[0]));

  //   /* Find control currents */
  //   for (i = 0; i < 3; i++)
  //   {
  //     /* Find the ideal control current */
  //     (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
  //         controlDipole_Sen_NmpT[i] /
  //         (p_jamSail_params_in->magnetorquer_params.coilArea_Sen_m2[i] *
  //          p_jamSail_params_in->magnetorquer_params.coilTurns_Sen[i]);

  //     /* Flatten ideal current to be within peak tolerances */
  //     if ((p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) >
  //         (p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]))
  //     {
  //       /* Ideal current is greater in positive direction */
  //       (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
  //           (p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]);
  //     }
  //     else if
  //     ((p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) <
  //              -(p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]))
  //     {
  //       /* Ideal current is greater in negative direction */
  //       (p_jamSail_state_inout->magnetorquer_state.inputCurrent_Sen_A[i]) =
  //           -(p_jamSail_params_in->magnetorquer_params.maxCurrent_Sen_A[i]);
  //     }
  //   }

  return GCONST_TRUE;
}