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
  int i;

  /* Clear and Free memory of dictionary */
  free(p_dic);
  p_dic = NULL;

  return GCONST_TRUE;
}
