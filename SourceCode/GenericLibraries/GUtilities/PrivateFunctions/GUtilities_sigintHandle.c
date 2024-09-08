/*
 *    @File:         GUtilities_sigintHandle.c
 *
 *    @Brief:        Function which catches a signint
 *
 *    @Date:         07/08/2024
 *
 */

#include <signal.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GUtilities/DataStructs/GUtilities_StateStructs.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

void GUtilities_sigintHandle(int signum_in)
{
  /* Send flag to end simulation */
  Utilities.runSimStatus = GCONST_FALSE;
}
