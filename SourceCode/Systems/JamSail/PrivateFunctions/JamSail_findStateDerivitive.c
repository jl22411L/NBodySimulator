/*!
 *    @File:         JamSail_findStateDerivitive.c
 *
 *    @Brief:        Private function which finds the state derivitive of
 *                   JamSail's EKF.
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

int JamSail_findStateDerivitive(JamSail_State  *p_jamSail_state_in,
                                JamSail_Params *p_jamSail_params_in,
                                double         *p_stateVector_in,
                                double          xxInertia_Bod_kgm2_in,
                                double          yyInertia_Bod_kgm2_in,
                                double          zzInertia_Bod_kgm2_in,
                                double         *p_stateDerivitiveVector_out)
{
  /* Declare local variables */
  double  dipoleEstimate_Sen_Am2[3];
  double  measuredMagneticField_Sen_T[3];
  double  torqueEstimate_Sen_Nm[3];
  double  torqueEstimate_Bod_Nm[3];
  double  invInertiaMatrix[3][3];
  double  angularMomentum_radkgm2_Bod[3];
  double  crossRotationalMoments_Nm_Bod[3];
  double  effectiveNetMoment_Nm_Bod[3];
  double  angularAcceleration_Bod_radps2[3];
  uint8_t i;

  /* Clearing local variables */
  GZero(&invInertiaMatrix[0][0], double[3][3]);
  GZero(&angularMomentum_radkgm2_Bod[0], double[3]);
  GZero(&crossRotationalMoments_Nm_Bod[0], double[3]);
  GZero(&effectiveNetMoment_Nm_Bod, double[3]);
  GZero(&(torqueEstimate_Sen_Nm[0]), double[3]);
  GZero(&(measuredMagneticField_Sen_T[0]), double[3]);
  GZero(&(torqueEstimate_Sen_Nm[0]), double[3]);
  GZero(&(torqueEstimate_Bod_Nm[0]), double[3]);
  GZero(&(angularAcceleration_Bod_radps2[0]), double[3]);

  /* Find estiamte for torque applied in sensor frame */
  for (i = 0; i < 3; i++)
  {
    dipoleEstimate_Sen_Am2[i] =
        (p_jamSail_state_in->magnetorquer_state.inputCurrent_Sen_A[i]) *
        (p_jamSail_params_in->magnetorquer_params.coilArea_Sen_m2[i]) *
        (p_jamSail_params_in->magnetorquer_params.coilTurns_Sen[i]);
  }

  /* Find measured magnetic field in Teslas */
  for (i = 0; i < 3; i++)
  {
    measuredMagneticField_Sen_T[i] =
        p_jamSail_state_in->magnetometer_state.measuredMagneticField_Sen_nT[i] *
        GCONST_NM_TOLERANCE;
  }

  /* Find torque estiamte in the sensor frame */
  GMath_crossProduct(&(dipoleEstimate_Sen_Am2[0]),
                     &(measuredMagneticField_Sen_T[0]),
                     &(torqueEstimate_Sen_Nm[0]));

  /* Find the torque in the body frame */
  GMath_quaternionPointRotation(&(torqueEstimate_Bod_Nm[0]),
                                &(torqueEstimate_Sen_Nm[0]),
                                &(p_jamSail_params_in->magnetorquer_params
                                      .actuatorQuaternion_BodToSen[0]));

  /* Make sure the quaternion is a unit quaternion */
  GMath_findUnitQuaternion(p_stateVector_in, p_stateVector_in);

  /* Find derivitive of quaternion */
  GMath_quaternionFrameRateCalc(p_stateDerivitiveVector_out,
                                (p_stateVector_in + 0),
                                (p_stateVector_in + 4));

  // TODO: Change from control torque

  /* Find the inverse of the inertia matrix */
  GMath_invMat(&(p_jamSail_state_in->p_satelliteBody_state->rigidBody_state
                     .inertiaMatrix_Bod_kgm2[0][0]),
               &invInertiaMatrix[0][0],
               3);

  /* Find the angular momentum of the rigid body */
  GMath_matMul(&(p_jamSail_state_in->p_satelliteBody_state->rigidBody_state
                     .inertiaMatrix_Bod_kgm2[0][0]),
               3,
               3,
               &p_jamSail_state_in->angularVelocityEstimate_Bod_rads[0],
               3,
               1,
               &angularMomentum_radkgm2_Bod[0]);

  /* Find the cross rotational inertia moements */
  GMath_crossProduct(&p_jamSail_state_in->angularVelocityEstimate_Bod_rads[0],
                     &angularMomentum_radkgm2_Bod[0],
                     &crossRotationalMoments_Nm_Bod[0]);

  /* Find the effective net moments */
  GMath_matSub(&p_jamSail_state_in->controlTorque_Bod_Nm[0],
               3,
               1,
               &crossRotationalMoments_Nm_Bod[0],
               3,
               1,
               &effectiveNetMoment_Nm_Bod[0]);

  /* Find the angular acceleration of the body */
  GMath_matMul(&invInertiaMatrix[0][0],
               3,
               3,
               &effectiveNetMoment_Nm_Bod[0],
               3,
               1,
               &angularAcceleration_Bod_radps2[0]);

  /* Transfer angular acceleration */
  for (i = 0; i < 3; i++)
  {
    *(p_stateDerivitiveVector_out + 4 + i) = angularAcceleration_Bod_radps2[i];
  }

  return GCONST_TRUE;
}