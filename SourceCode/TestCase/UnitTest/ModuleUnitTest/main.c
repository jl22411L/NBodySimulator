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
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int main()
{
  double A[5][5] = {
      {1, 2, 3, 4, 5},
      {5, 4, 3, 2, 1},
      {1, 2, 4, 1, 5},
      {4, 8, 7, 2, 9},
      {2, 1, 6, 4, 2}};

  double invA[5][5];

  GZero(&invA, double[5][5]);

  GMath_invMat(&A[0][0], &invA[0][0], 5);

  int i;
  int j;

  for (i = 0; i < 5; i++)
  {
    for (j = 0; j < 5; j++)
    {
      printf("%lf, ", invA[i][j]);
    }
    printf("\n");
  }

  return GCONST_EXIT_SUCCESS;
}
