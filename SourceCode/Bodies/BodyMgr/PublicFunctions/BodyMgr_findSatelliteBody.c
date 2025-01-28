/*!
 *    @File:         BodyMgr_findBody.c
 *
 *    @Brief:        Function which will find a body with a specific name.
 *
 *    @Date:         28/01/2025
 *
 */

#include <stdint.h>
#include <string.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int BodyMgr_findSatelliteBody(BodyMgr_State        *p_bodyMgr_state_in,
                              SatelliteBody_State **p_satelliteBody_state_out,
                              const char           *p_bodyName)
{
  /* Declare local variables */
  uint16_t i;

  /* Iterate through the satellite bodies until a name matches */
  for (i = 0; i < p_bodyMgr_state_in->nSatelliteBodies; i++)
  {
    /* Compare the name of the body with the inputted name */
    if (strcmp(p_bodyName,
               &((*(p_bodyMgr_state_in->p_satelliteBodyList + i))
                     ->rigidBody_state.bodyName[0])) == GCONST_FALSE)
    {
      /* Store the address of the body */
      *(p_satelliteBody_state_out) =
          *(p_bodyMgr_state_in->p_satelliteBodyList + i);

      /* Return GCONST_TRUE to indicate that the body was found successfully */
      return GCONST_TRUE;
    }
  }

  /*!
   * If this stage of the function is reached, no body with the inputted name
   * has been found. Hence, an error has occured and a GCONST_FALSE is returned.
   */
  return GCONST_FALSE;
}