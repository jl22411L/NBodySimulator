/*!
 *    @File:         BodyMgr_findCeletialBody.c
 *
 *    @Brief:        Function which will find a celestial body with a specific
 *                   name.
 *
 *    @Date:         29/01/2025
 *
 */

#include <stdint.h>
#include <string.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyMgr/DataStructs/BodyMgr_StateStruct.h"
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int BodyMgr_findCelestialBody(BodyMgr_State        *p_bodyMgr_state_in,
                              CelestialBody_State **p_celestialBody_state_out,
                              const char           *p_bodyName)
{
  /* Declare local variables */
  uint16_t i;

  /* Iterate through the celestial bodies until a name matches */
  for (i = 0; i < p_bodyMgr_state_in->nCelestialBodies; i++)
  {
    /* Compare the name of the body with the inputted name */
    if (strcmp(p_bodyName,
               &((*(p_bodyMgr_state_in->p_celestialBodyList + i))
                     ->rigidBody_state.bodyName[0])) == GCONST_FALSE)
    {
      /* Store the address of the body */
      *(p_celestialBody_state_out) =
          *(p_bodyMgr_state_in->p_celestialBodyList + i);

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