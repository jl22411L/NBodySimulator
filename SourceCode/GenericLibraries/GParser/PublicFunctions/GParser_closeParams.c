/*
 *    @File:         GParser_closeParams.c
 *
 *    @ Brief:       Frees memory used for loading content in GParser module
 *
 *    @ Date:        06/01/2024
 *
 */

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

/*
 *  Refer to respective header file for function description
 */
int GParser_closeParams(dictionary **p_dic)
{
  /* Clearing dictionary from heap memory */
  free(p_dic);

  return GCONST_TRUE;
}