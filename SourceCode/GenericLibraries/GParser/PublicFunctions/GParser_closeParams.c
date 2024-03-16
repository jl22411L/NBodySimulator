/*
 *    @File:         GParser_closeParams.c
 *
 *    @ Brief:       Frees memory used for loading content in GParser module
 *
 *    @ Date:        06/01/2024
 *
 */

#include <stdio.h>
#include <stdlib.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_closeParams(GParser_State *p_GParser_state, dictionary *p_dic)
{
  /* Declaring local variables */
  int8_t i;
  int8_t j;

  for (i = 0; i < p_GParser_state->maxNumberSection; i++)
  {
    /* Free data of individual keys and there values */
    for (j = 0; j < p_GParser_state->sizeIndex; j++)
    {
      free(((p_dic + i)->key + j));

      free(((p_dic + i)->value + j));
    }
    /* Clear and Free data related to section */
    free((p_dic + i)->key);

    /* Clear and Free data related to key */
    free((p_dic + i)->value);
  }

  /* Clear and Free memory of dictionary */
  free(p_dic);

  return GCONST_TRUE;
}
