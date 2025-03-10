/*!
 *    @File:         JamSail_fillStateJacobian.c
 *
 *    @Brief:        Private function which will fill the state jacobian for
 *                   the EKF.
 *
 *    @Date:         08/03/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int JamSail_fillStateJacobian(JamSail_State *p_jamSail_state_out,
                              double         xxInertia_Bod_kgm2_in,
                              double         yyInertia_Bod_kgm2_in,
                              double         zzInertia_Bod_kgm2_in)
{
  /* Declare local variables */
  /* None */

  /* Fill each component of the state jacobian manually */
  (p_jamSail_state_out->stateJacobian[0][1]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_out->stateJacobian[0][2]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_out->stateJacobian[0][3]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_out->stateJacobian[1][0]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_out->stateJacobian[1][2]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_out->stateJacobian[1][3]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_out->stateJacobian[2][0]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_out->stateJacobian[2][1]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_out->stateJacobian[2][3]) =
      0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]);
  (p_jamSail_state_out->stateJacobian[3][0]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]);
  (p_jamSail_state_out->stateJacobian[3][1]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]);
  (p_jamSail_state_out->stateJacobian[3][2]) =
      -0.5 * (p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]);

  (p_jamSail_state_out->stateJacobian[0][4]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_out->stateJacobian[0][5]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  (p_jamSail_state_out->stateJacobian[0][6]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_out->stateJacobian[1][4]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);
  (p_jamSail_state_out->stateJacobian[1][5]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_out->stateJacobian[1][6]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_out->stateJacobian[2][4]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_out->stateJacobian[2][5]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_out->stateJacobian[2][6]) =
      0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]);
  (p_jamSail_state_out->stateJacobian[3][4]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[0]);
  (p_jamSail_state_out->stateJacobian[3][5]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[1]);
  (p_jamSail_state_out->stateJacobian[3][6]) =
      -0.5 * (p_jamSail_state_out->quaternionEstimate_InertCenToBod[2]);

  (p_jamSail_state_out->stateJacobian[4][5]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]) *
      (zzInertia_Bod_kgm2_in - yyInertia_Bod_kgm2_in) / xxInertia_Bod_kgm2_in;
  (p_jamSail_state_out->stateJacobian[4][6]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]) *
      (zzInertia_Bod_kgm2_in - yyInertia_Bod_kgm2_in) / xxInertia_Bod_kgm2_in;
  (p_jamSail_state_out->stateJacobian[5][4]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[2]) *
      (xxInertia_Bod_kgm2_in - zzInertia_Bod_kgm2_in) / yyInertia_Bod_kgm2_in;
  (p_jamSail_state_out->stateJacobian[5][6]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]) *
      (xxInertia_Bod_kgm2_in - zzInertia_Bod_kgm2_in) / yyInertia_Bod_kgm2_in;
  (p_jamSail_state_out->stateJacobian[6][4]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[1]) *
      (yyInertia_Bod_kgm2_in - xxInertia_Bod_kgm2_in) / zzInertia_Bod_kgm2_in;
  (p_jamSail_state_out->stateJacobian[6][5]) =
      -(p_jamSail_state_out->angularVelocityEstimate_Bod_rads[0]) *
      (yyInertia_Bod_kgm2_in - xxInertia_Bod_kgm2_in) / zzInertia_Bod_kgm2_in;

  return GCONST_TRUE;
}