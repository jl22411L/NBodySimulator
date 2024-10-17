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
  int    i;
  int    j;
  double input;
  double schmidtCoefficentArray[14][14];

  /* Clear Arrays */
  GZero(&(schmidtCoefficentArray[0][0]), double[14][14]);

  GLegPoly_findSchmidtQuasiNormFactors(&(schmidtCoefficentArray[0][0]), 13);

  j = 0;
  for (i = 0; i <= 13; i++)
  {
    printf("%lf", schmidtCoefficentArray[i][j]);

    for (j = 1; j <= 13; j++)
    {
      printf(",%lf", schmidtCoefficentArray[i][j]);
    }

    printf("\n");
  }
  printf("\n\n");

  return GCONST_EXIT_SUCCESS;
}
