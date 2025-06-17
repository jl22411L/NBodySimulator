/*!
 *    @File:         JamSail_terminate.c
 *
 *    @Brief:        Private function to terminate JamSail
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
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int JamSail_terminate(JamSail_State *p_jamSail_state_out)
{
  /* Declare local variables */
  /* None */

  /* Close archive for JamSail's ADCS */
  GArchive_close(&(p_jamSail_state_out->attitudeDeterminationArchive));

  return GCONST_TRUE;
}