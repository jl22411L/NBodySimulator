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

  double P[3][3]     = {{1, 2, 3}, {3, 4, 5}, {6, 7, 8}};
  double H[2][3]     = {{7, 8, 9}, {10, 11, 12}};
  double inter[2][2] = {{1, 2}, {3, 4}};
  double K[3][2]     = {{0, 0}, {0, 0}, {0, 0}};

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfDegreeM_in; j++)
    {
      for (k = 0; k < ekfDegreeM_in; k++)
      {
        for (l = 0; l < ekfOrderN_in; l++)
        {
          K[i][j] += P[i][l] * H[k][l] * inter[k][j];
        }
      }
    }
  }

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfDegreeM_in; j++)
    {
      printf("%lf ", K[i][j]);
    }
    printf("\n");
  }

  return GCONST_EXIT_SUCCESS;
}
