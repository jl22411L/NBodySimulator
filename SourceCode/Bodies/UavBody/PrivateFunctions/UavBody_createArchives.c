/*
 *    @File:         UavBody_createArchives.c
 *
 *    @ Brief:       Creates archives for UavBody
 *
 *    @ Date:        02/05/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int UavBody_createArchives(
    UavBody_State *p_uavBody_state_in,
    const char    *p_bodyName_in)
{
  /* Defining local variables */
  char buffer[GCONST_BUFFER_1024];

  /* Clearing buffer */
  GZero(&buffer[0], char[GCONST_BUFFER_1024]);

  /* Create directory to body archive */
  sprintf(buffer, "Bodies/%s/OutputData/UavBody", p_bodyName_in);

  /* Create archive */
  GArchive_init(&p_uavBody_state_in->uavBodyArchive, buffer);

  /* Write header for archive */
  GArchive_writeHeader(&p_uavBody_state_in->uavBodyArchive);

  /*-------------------------------------------------------------------------*
   *                             UAV BODY STATE                              *
   *-------------------------------------------------------------------------*/
  /* None */

  return GCONST_TRUE;
}
