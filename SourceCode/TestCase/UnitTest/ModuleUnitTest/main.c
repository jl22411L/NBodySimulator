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
#include "GLegendrePoly/PublicFunctions/GLegendrePoly_PublicFunctions.h"
#include "GZero/GZero.h"

int main(void)
{
  /* Declare local variables */
  int    i;
  int    j;
  double input;
  double outputArray[14][14];
  double outputArray2[14][14];
  double outputDerArray[14][14];

  input = cos(90 * GCONST_DEG_TO_RAD);

  GZero(&outputArray[0][0], double[14][14]);
  GZero(&outputArray2[0][0], double[14][14]);
  GZero(&outputDerArray[0][0], double[14][14]);

  GLegendrePoly_findAssociatedArrayOutput(&outputArray[0][0], input, 13);
  GLegendrePoly_findAssociatedArrayOutput(
      &outputArray2[0][0],
      input + 0.000001,
      13);
  GLegendrePoly_findAssociatedDerivitiveArrayOutput(
      &outputDerArray[0][0],
      &outputArray[0][0],
      input,
      13);

  printf("Legendre Polynomial\n\n");
  for (i = 0; i <= 13; i++)
  {
    for (j = 0; j <= 13; j++)
    {
      printf("%lf, ", outputArray[i][j]);
    }
    printf("\n");
  }

  printf("\nLegendre Der Polynomial\n\n");
  for (i = 0; i <= 13; i++)
  {
    for (j = 0; j <= 13; j++)
    {
      printf("%lf, ", outputDerArray[i][j]);
    }
    printf("\n");
  }

  printf("\nLegendre Der2 Polynomial\n\n");
  for (i = 0; i <= 13; i++)
  {
    for (j = 0; j <= 13; j++)
    {
      printf("%lf, ", (outputArray[i][j] - outputArray2[i][j]) / 0.000001);
    }
    printf("\n");
  }

  return GCONST_EXIT_SUCCESS;
}
