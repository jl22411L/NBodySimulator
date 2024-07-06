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
#include "Guidance/TriadAlgorithm/PublicFunctions/TriadAlgorithm_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"

#define rowsA (2)
#define colsA (3)

#define rowsB (2)
#define colsB (3)

int main(void)
{
  double vector1_fix[3] = {2, 5, 4};
  double vector1_bod[3] = {2.2276, 3.5895, 5.2109};

  double vector2_fix[3] = {3, 9, 7};
  double vector2_bod[3] = {3.3862, 6.4439, 9.2741};

  double test[3] = {0, 0, 0};

  double q[4];

  double A[3][3] = {
      {0.9810603, -0.0858316, 0.1736482},
      {0.1410648, 0.9309405, -0.3368241},
      {-0.1327460, 0.3549404, 0.9254166}};

  GMath_quaternion2Dcm(&q[0], &A[0][0]);

  TriadAlgorithm_getQuat(
      &vector1_bod[0],
      &vector1_fix[0],
      &vector2_bod[0],
      &vector2_fix[0],
      &q[0]);

  GMath_quaternionPointRotation(&test[0], &vector1_fix[0], &q[0]);

  return GCONST_EXIT_SUCCESS;
}
