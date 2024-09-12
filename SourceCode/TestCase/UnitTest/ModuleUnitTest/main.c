/*
 *    @File:         main.c
 *
 *    @ Brief:       ModuleUnitTest
 *
 *    @ Date:        02/03/2024
 *
 */

#include <stdio.h>

/* Function Includes */
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int main(void)
{
  Igrf_Params igrfParams;

  GZero(&igrfParams, Igrf_Params);

  Igrf_init(&igrfParams, "Parameters/Igrf2020To2025Parameters.ini");

  return GCONST_EXIT_SUCCESS;
}
