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
  double  angularMomentum_radkgm2_Bod[3];
  double  crossRotationalMoments_Nm_Bod[3];
  uint8_t i;

  /* Clear local variables */
  GZero(&(angularMomentum_radkgm2_Bod[0]), double[3]);
  GZero(&(crossRotationalMoments_Nm_Bod[0]), double[3]);

  /* ------------------------------------------------------------------------ *
   * Error Vector Calcaultions
   * ------------------------------------------------------------------------ */

  /* Find error quaternion */
  p_jamSail_state_inout->errorQuaternion_InertCenToBod[0] =
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[1] =
      -(p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[2] =
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) -
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) -
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

  p_jamSail_state_inout->errorQuaternion_InertCenToBod[3] =
      (p_requiredQuaternion_InertCenToBod_in[0]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]) +
      (p_requiredQuaternion_InertCenToBod_in[1]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[1]) +
      (p_requiredQuaternion_InertCenToBod_in[2]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[2]) +
      (p_requiredQuaternion_InertCenToBod_in[3]) *
          (p_jamSail_state_inout->quaternionEstimate_InertCenToBod[3]);

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

  return GCONST_TRUE;
}