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

#define rowsA (3)
#define colsA (4)

#define rowsB (4)
#define colsB (2)

int main()
{

  double A[rowsA][colsA] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {1, 2, 3, 4}};

  double B[rowsB][colsB] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};

  double C[rowsA][colsB];

  GZero(&C[0][0], double[rowsA][colsB]);

  GMath_matMul(&A[0][0], rowsA, colsA, &B[0][0], rowsB, colsB, &C[0][0]);

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

  return GCONST_EXIT_SUCCESS;
}
