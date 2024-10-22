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
  GZero(p_GParser_state->sectionBuffer, char[1024]);
  GZero(p_GParser_state->keyBuffer, char[1024]);
  GZero(p_GParser_state->valueBuffer, char[1024]);

  /* Clear Index's */
  GZero(&p_GParser_state->sizeArrayIndex, uint16_t);
  GZero(&p_GParser_state->sectionIndex, uint32_t);
  GZero(&p_GParser_state->valueArrayIndex, uint32_t);
  GZero(&p_GParser_state->keyArrayIndex, uint32_t);

  /* Clear size variables */
  GZero(&p_GParser_state->keySize, int[256]);
  GZero(&p_GParser_state->valueSize, int[256]);
  GZero(&p_GParser_state->sectionSize, int);

  return GCONST_TRUE;
}
