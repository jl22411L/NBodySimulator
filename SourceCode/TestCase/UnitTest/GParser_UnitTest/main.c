/*
 *   @File:         main.c
 *
 *   @ Brief:       Unit test of GParser Library
 *
 *   @ Description:
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GParser/GParser.h"

int main()
{
  dictionary **p_dic;
  GParser_loadParams("Parameters/test.ini", p_dic);

  return GCONST_EXIT_SUCCESS;
}