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
/* None */

/* Structure Include */
/* None */
/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

int main(void)
{
  /* Declare local variables */
  int ekfOrderN_in  = 3;
  int ekfDegreeM_in = 2;
  int i;
  int j;
  int k;
  int l;

  double P[3][3]        = {{1, 2, 3}, {3, 4, 5}, {6, 7, 8}};
  double H[2][3]        = {{7, 8, 9}, {10, 11, 12}};
  double updatedP[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
  double K[3][2]        = {{1, 2}, {3, 4}, {5, 6}};

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      for (k = 0; k < ekfDegreeM_in; k++)
      {
        for (l = 0; l < ekfOrderN_in; l++)
        {
          updatedP[i][j] -= K[i][k] * H[k][l] * P[l][j];
        }
      }

      updatedP[i][j] += P[i][j];
    }
  }

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      printf("%lf ", updatedP[i][j]);
    }
    printf("\n");
  }

  return GCONST_EXIT_SUCCESS;
}
