/*!
 *    @File:         ContinuousEkf_stepCovariance.c
 *
 *    @Brief:        Private function definition which will integrate the
 *                   covariance derivitive.
 *
 *    @Date:         04/03/2025
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

int ContinuousEkf_stepCovariance(double *p_systemCovarianceDerivitive_in,
                                 double *p_previousSystemCovariance_in,
                                 double  timeStep_s_in,
                                 uint8_t ekfOrderN_in,
                                 double *p_currentSystemCovariance_out)
{
  /* Declare local variables */
  uint8_t i;
  uint8_t j;

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      *(p_currentSystemCovariance_out + ekfOrderN_in * i + j) =
          *(p_previousSystemCovariance_in + ekfOrderN_in * i + j) +
          timeStep_s_in(
              *(p_systemCovarianceDerivitive_in + ekfOrderN_in * i + j));
    }
  }

  return GCONST_TRUE;
}