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
#include "UavBody/ConstantDefs/UavBody_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int UavBody_createArchives(
    UavBody_State *p_uavBody_state_in,
    const char    *p_bodyName_in)
{
  /* Defining local variables */
  char buffer[UAVBODY_CREATE_ARCHIVE_BUFFER];

  /* Clearing buffer */
  GZero(&buffer[0], char[UAVBODY_CREATE_ARCHIVE_BUFFER]);

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
