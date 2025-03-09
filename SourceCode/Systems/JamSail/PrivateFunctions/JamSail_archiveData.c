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

  /* Archive the estimated angular velocity */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                    (p_jamSail_state_in->angularVelocityEstimate_Bod_rads)[i]);
  }

  /* Archive the flag to indicate if attitude was estimated or measured */
  GArchive_addVal(&(p_jamSail_state_in->attitudeDeterminationArchive),
                  (double)(p_jamSail_state_in->attitudeMeasuredFlag));

  /* Write row for archive*/
  GArchive_writeLine(&(p_jamSail_state_in->attitudeDeterminationArchive));

  return GCONST_TRUE;
}