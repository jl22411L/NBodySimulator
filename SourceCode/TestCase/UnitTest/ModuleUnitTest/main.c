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

#define rowsA (2)
#define colsA (3)

#define rowsB (2)
#define colsB (3)

int main()
{

  double vectorIn[3]       = {0, 0, 1};
  double vectorOut1[3]     = {0, 0, 0};
  double vectorOut2[3]     = {0, 0, 0};
  double quaternion[4]     = {0.1913417, 0.4619398, 0.1913417, 0.8446232};
  double unitQuaternion[4] = {0, 0, 0, 0};
  int    i;

  /* Find unit quaternion */
  GMath_findUnitQuaternion(&quaternion[0], &unitQuaternion[0]);

  /* Apply rotateion */
  GMath_quaternionPointRotation(
      &vectorIn[0],
      &unitQuaternion[0],
      &vectorOut1[0]);
  GMath_quaternionFrameRotation(
      &vectorOut1[0],
      &unitQuaternion[0],
      &vectorOut2[0]);

  /* Display output */
  for (i = 0; i < 3; i++)
  {
    printf("%lf, ", vectorOut1[i]);
  }
  printf("\n");
  for (i = 0; i < 3; i++)
  {
    printf("%lf, ", vectorOut2[i]);
  }

  return GCONST_EXIT_SUCCESS;
}
