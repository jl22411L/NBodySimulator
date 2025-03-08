/*
 *    @File:         GMath_findUnitQuaternion.c
 *
 *    @Brief:        Finds the unit quaternion
 *
 *    @Date:         15/05/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "GMath/PublicFunctions/GMath_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_findUnitQuaternion(double *p_inputQuaternion_in,
                             double *p_outputQuaternion_out)
{
  /* Declare local variables */
  double  quaternionMagnitude;
  uint8_t i;

  /* Find the magnitude of the quaternion */
  GMath_vectorMag(&quaternionMagnitude, p_inputQuaternion_in, 4);

  /* Sscale quaternion to make it a unit quaternion */
  for (i = 0; i < 4; i++)
  {
    if (*(p_inputQuaternion_in + 3) < 0.0)
    {
      *(p_outputQuaternion_out + i) =
          *(p_inputQuaternion_in + i) / -quaternionMagnitude;
    }
    else
    {
      *(p_outputQuaternion_out + i) =
          *(p_inputQuaternion_in + i) / quaternionMagnitude;
    }
  }

  return GCONST_TRUE;
}
