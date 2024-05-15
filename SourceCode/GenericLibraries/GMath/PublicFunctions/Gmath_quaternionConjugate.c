/*
 *    @File:         GMath_quaternionConjugate.c
 *
 *    @Brief:        Finds the quaternion conjugate
 *
 *    @Date:         15/05/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_quaternionConjugate(
    double *p_inputQuaternion_in,
    double *p_outputQuaternion_out)
{
  /* Define local variables */
  uint8_t i;

  /* Iterate through the gibbs poriton of the quaternion */
  for (i = 0; i < 3; i++)
  {
    /* Switch the sign of the gibs components of the quaternion */
    *(p_outputQuaternion_out + i) = -*(p_inputQuaternion_in + i);
  }

  /* Copy the scaler portion of the quaternion */
  *(p_outputQuaternion_out + 3) = *(p_inputQuaternion_in + 3);

  return GCONST_TRUE;
}
