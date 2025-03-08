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

int ContinuousEkf_stepCovariance(double *p_errorCovarianceDerivitive_in,
                                 double  timeStep_s_in,
                                 uint8_t ekfOrderN_in,
                                 double *p_errorCovariance_inout)
{
  /* Declare local variables */
  uint8_t i;
  uint8_t j;

  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      *(p_errorCovariance_inout + ekfOrderN_in * i + j) +=
          timeStep_s_in *
          (*(p_errorCovarianceDerivitive_in + ekfOrderN_in * i + j));
    }
  }

  return GCONST_TRUE;
}