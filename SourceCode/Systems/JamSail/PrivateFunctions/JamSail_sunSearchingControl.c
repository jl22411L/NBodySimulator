/*
 *    @File:         JamSail_sunSearchingControl.c
 *
 *    @Brief:        Funciton definition for snu trakcking control.
 *
 *    @Date:         13/04/2025
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

int JamSail_sunSearchingControl(JamSail_State  *p_jamSail_state_inout,
                                JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double  controlDipole_Bod_NmpT[3];
  double  controlDipole_Sen_NmpT[3];
  double  measuredMagneticField_Bod_nT[3];
  double  angularMomentum_radkgm2_Bod[3];
  double  crossRotationalMoments_Nm_Bod[3];
  double  magneticFieldMagnitude_nT;
  uint8_t i;

  /* Clear local variables */
  GZero(&(controlDipole_Bod_NmpT[0]), double[3]);
  GZero(&(controlDipole_Sen_NmpT[0]), double[3]);
  GZero(&(measuredMagneticField_Bod_nT[0]), double[3]);
  GZero(&(angularMomentum_radkgm2_Bod[0]), double[3]);
  GZero(&(crossRotationalMoments_Nm_Bod[0]), double[3]);

  /* Find the angular momentum of the rigid body */
  GMath_matMul(&(p_jamSail_state_inout->p_satelliteBody_state->rigidBody_state
                     .inertiaMatrix_Bod_kgm2[0][0]),
               3,
               3,
               &(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]),
               3,
               1,
               &angularMomentum_radkgm2_Bod[0]);

  /* Find the cross rotational inertia moements */
  GMath_crossProduct(
      &(p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0]),
      &(angularMomentum_radkgm2_Bod[0]),
      &(crossRotationalMoments_Nm_Bod[0]));

  /* Find control torque */
  (p_jamSail_state_inout->controlTorque_Bod_Nm[0]) =
      (p_jamSail_params_in->detumblingProportionalCoefficient[0]) *
          (0.034907 -
           (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[0])) +
      crossRotationalMoments_Nm_Bod[0];

  (p_jamSail_state_inout->controlTorque_Bod_Nm[1]) =
      -(p_jamSail_params_in->detumblingProportionalCoefficient[1]) *
          (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[1]) +
      crossRotationalMoments_Nm_Bod[1];

  (p_jamSail_state_inout->controlTorque_Bod_Nm[2]) =
      -(p_jamSail_params_in->detumblingProportionalCoefficient[2]) *
          (p_jamSail_state_inout->angularVelocityEstimate_Bod_rads[2]) +
      crossRotationalMoments_Nm_Bod[2];

  return GCONST_TRUE;
}