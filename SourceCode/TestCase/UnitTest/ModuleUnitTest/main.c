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

int main(void)
{
  double quaternion[4] = {0, 0, 0, 1};
  double eul123_rad[3] = {0, 0, 0};
  double dcm[3][3]     = {
      {0.8528686, 0.0052361, 0.5220994},
      {0.1503837, 0.9551122, -0.2552361},
      {-0.5000000, 0.2961981, 0.8137977}};
  int i;
  int j;

  GMath_dcm2Eul(&dcm[0][0], &eul123_rad[0]);

  for (i = 0; i < 3; i++)
  {
    printf("%lf,", eul123_rad[i]);
  }

  printf("\n\n");

  GMath_eul2Dcm(&eul123_rad[0], &dcm[0][0]);

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      printf("%lf, ", dcm[i][j]);
    }
    printf("\n");
  }

  printf("\n\n");

  GMath_dcm2Quat(&dcm[0][0], &quaternion[0]);

  for (i = 0; i < 4; i++)
  {
    printf("%lf, ", quaternion[i]);
  }

  printf("\n\n");

  GMath_quaternion2Dcm(&quaternion[0], &dcm[0][0]);

  for (i = 0; i < 3; i++)
  {
    for (j = 0; j < 3; j++)
    {
      printf("%lf, ", dcm[i][j]);
    }
    printf("\n");
  }

  printf("\n\n");

  GMath_quaternion2Eul(&quaternion[0], &eul123_rad[0]);

  for (i = 0; i < 3; i++)
  {
    printf("%lf, ", eul123_rad[i]);
  }

  printf("\n\n");

  GMath_eul2Quat(&eul123_rad[0], &quaternion[0]);

  for (i = 0; i < 4; i++)
  {
    printf("%lf, ", quaternion[i]);
  }

  return GCONST_EXIT_SUCCESS;
}
