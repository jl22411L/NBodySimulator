/*
 *    @File:         UavBody_archiveData.c
 *
 *    @ Brief:       Archives the bodies state members
 *
 *    @ Date:        02/05/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"

/* Structure Include */
#include "UavBody/DataStructs/UavBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int UavBody_archiveData(UavBody_State *p_uavBody_state_in)
{
  /* Write values to CSV file */
  GArchive_writeLine(&p_uavBody_state_in->uavBodyArchive);

  return GCONST_TRUE;
}
