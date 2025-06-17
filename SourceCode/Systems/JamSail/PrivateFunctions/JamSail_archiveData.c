/*!
 *    @File:         JamSail_archiveData.c
 *
 *    @Brief:
 *
 *    @Date:         08/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int JamSail_archiveData(JamSail_State *p_jamSail_state_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Archive the quaternion estimate elements */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->quaternionEstimate_InertCenToBod)[i]);
  }

  /* Archive the required quaternion estimate elements */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->requiredQuaternion_InertCenToBod)[i]);
  }

  /* Archive the error quaternion estimate elements */
  for (i = 0; i < 4; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->errorQuaternion_InertCenToBod)[i]);
  }

  /* Archive the estimated angular velocity */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->angularVelocityEstimate_Bod_rads)[i]);
  }

  /* Archive the estimated position of JamSail */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->positionEstimate_InertCen_m)[i]);
  }

  /* Archive the control Torque */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->controlTorque_Bod_Nm)[i]);
  }

  /* Archive the currents of magnetorquer */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &(p_jamSail_state_in->attitudeDeterminationArchive),
        p_jamSail_state_in->magnetorquer_state.inputCurrent_Sen_A[i]);
  }

  /* Archive the flag to indicate if attitude was estimated or measured */
  GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                  (double)(p_jamSail_state_in->attitudeMeasuredFlag));

  /* Archive ADCS state */
  GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                  (double)(p_jamSail_state_in->adcsState));

  /* Write row for archive*/
  GArchive_writeLine(&(p_jamSail_state_in->attitudeDeterminationArchive));

  return GCONST_TRUE;
}