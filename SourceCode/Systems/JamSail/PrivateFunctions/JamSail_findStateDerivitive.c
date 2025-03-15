/*!
 *    @File:         JamSail_findStateDerivitive.c
 *
 *    @Brief:        Private function which finds the state derivitive of
 *                   JamSail's EKF.
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
#include "GMath/GMath.h"

int JamSail_findStateDerivitive(JamSail_State *p_jamSail_state_in,
                                double        *p_stateVector_in,
                                double         xxInertia_Bod_kgm2_in,
                                double         yyInertia_Bod_kgm2_in,
                                double         zzInertia_Bod_kgm2_in,
                                double        *p_stateDerivitiveVector_out)
{
  /* Declare local variables */
  /* None */

  /* Find derivitive of quaternion */
  GMath_quaternionRateCalc(p_stateDerivitiveVector_out,
                           (p_stateVector_in + 0),
                           (p_stateVector_in + 4));

  /* Find derivitive of angular velocity x component */
  *(p_stateDerivitiveVector_out + 4) =
      ((p_jamSail_state_in->magnetorquer_state.totalTorque_Bod_Nm[0]) -
       (zzInertia_Bod_kgm2_in - yyInertia_Bod_kgm2_in) *
           (*(p_stateVector_in + 5)) * (*(p_stateVector_in + 6))) /
      xxInertia_Bod_kgm2_in;

  /* Find derivitive of angular velocity y component */
  *(p_stateDerivitiveVector_out + 5) =
      ((p_jamSail_state_in->magnetorquer_state.totalTorque_Bod_Nm[1]) -
       (xxInertia_Bod_kgm2_in - zzInertia_Bod_kgm2_in) *
           (*(p_stateVector_in + 4)) * (*(p_stateVector_in + 6))) /
      yyInertia_Bod_kgm2_in;

  /* Find derivitive of angular velocity z component */
  *(p_stateDerivitiveVector_out + 6) =
      ((p_jamSail_state_in->magnetorquer_state.totalTorque_Bod_Nm[2]) -
       (yyInertia_Bod_kgm2_in - xxInertia_Bod_kgm2_in) *
           (*(p_stateVector_in + 4)) * (*(p_stateVector_in + 5))) /
      zzInertia_Bod_kgm2_in;

  return GCONST_TRUE;
}