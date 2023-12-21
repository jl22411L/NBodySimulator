/*
 *    @File:         GParser_clearBuffers.c
 *
 *    @ Brief:       Clear buffers of state struct
 *
 *    @ Date:        20/12/2023
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GParser_clearBuffers(GParser_State *p_stateStruct)
{
  /* Clear Buffers */
  GClear(&p_stateStruct->sectionBuffer, 1024, char);
  GClear(&p_stateStruct->keyBuffer, 1024, char);
  GClear(&p_stateStruct->valueBuffer, 1024, char);

  /* Clear Indexes */
  GZero(&p_stateStruct->sizeIndex, uint8_t);
  GZero(&p_stateStruct->sectionIndex, uint8_t);
  GZero(&p_stateStruct->valueIndex, uint8_t);
  GZero(&p_stateStruct->keyIndex, uint8_t);

  GClear(&p_stateStruct->keySize, 256, int);
  GClear(&p_stateStruct->valueSize, 256, int);
  GZero(&p_stateStruct->sectionSize, int);

  return GCONST_TRUE;
}
