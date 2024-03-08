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

#define rowsA (2)
#define colsA (3)

#define rowsB (2)
#define colsB (3)

int main()
{

  double A[rowsA][colsA] = {{1, 2, 3}, {1, 2, 3}};

  double B[rowsB][colsB] = {{1, 2, 3}, {1, 2, 3}};

  double C[rowsA][colsB];

  GZero(&C[0][0], double[rowsA][colsB]);

  GMath_matAdd(&A[0][0], rowsA, colsA, &B[0][0], rowsB, colsB, &C[0][0]);

  int i;
  int j;

  for (i = 0; i < rowsA; i++)
  {
    for (j = 0; j < colsB; j++)
    {
      printf("%lf, ", C[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  GZero(&C[0][0], double[rowsA][colsB]);

  GMath_matSub(&A[0][0], rowsA, colsA, &B[0][0], rowsB, colsB, &C[0][0]);

  for (i = 0; i < rowsA; i++)
  {
    for (j = 0; j < colsB; j++)
    {
      printf("%lf, ", C[i][j]);
    }
    printf("\n");
  }

  return GCONST_EXIT_SUCCESS;
}
