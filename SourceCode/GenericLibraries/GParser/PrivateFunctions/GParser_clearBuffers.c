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

/*
 *  Refer to respective header file for function description
 */
int GParser_clearBuffers(GParser_State *p_GParser_state)
{
  /* Clear Buffers */
  GClear(p_GParser_state->sectionBuffer, 1024, char);
  GClear(p_GParser_state->keyBuffer, 1024, char);
  GClear(p_GParser_state->valueBuffer, 1024, char);

  /* Clear Index's */
  GZero(&p_GParser_state->sizeIndex, uint8_t);
  GZero(&p_GParser_state->sectionIndex, uint8_t);
  GZero(&p_GParser_state->valueIndex, uint8_t);
  GZero(&p_GParser_state->keyIndex, uint8_t);

  /* Clear size variables */
  GClear(&p_GParser_state->keySize, 256, int);
  GClear(&p_GParser_state->valueSize, 256, int);
  GClear(&p_GParser_state->sectionSize, 1, int);

  return GCONST_TRUE;
}
