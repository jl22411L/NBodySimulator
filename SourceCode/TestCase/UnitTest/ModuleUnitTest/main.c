/*
 *    @File:         main.c
 *
 *    @ Brief:       ModuleUnitTest
 *
 *    @ Date:        02/03/2024
 *
 */

#include <math.h>
#include <stdio.h>

/* Function Includes */
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLegPoly/PublicFunctions/GLegPoly_PublicFunctions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

#define step 1e-10

int main(void)
{
  /* Declare local variables */
  Igrf_Params igrf_params;

  /* Clear Arrays */
  GZero(&igrf_params, Igrf_Params);

  Igrf_init(&igrf_params, "Parameters/IgrfParameters.ini", 13, 13);

  return GCONST_EXIT_SUCCESS;
}
