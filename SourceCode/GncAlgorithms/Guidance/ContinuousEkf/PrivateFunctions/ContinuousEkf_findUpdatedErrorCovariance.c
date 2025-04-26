/*!
 *    @File:         ContinuousEkf_findUpdatedErrorCovariance.c
 *
 *    @Brief:        Private function definition to find the error covariance.
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
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int ContinuousEkf_findUpdatedErrorCovariance(
    double *p_kalmanGain_in,
    double *p_measurementJacobian_in,
    double *p_errorCovariance_inout,
    double *p_updatedErrorCovarianceBuffer_in,
    uint8_t ekfOrderN_in,
    uint8_t ekfDegreeM_in)
{
  /* Declare local variables */
  double  buffer1[7][7];
  double  buffer2[7][7];
  uint8_t i;
  uint8_t j;

  /* Clear variables */
  GZero(&buffer1[0][0], double[7][7]);
  GZero(&buffer2[0][0], double[7][7]);

  GMath_matMul(p_kalmanGain_in,
               7,
               9,
               p_measurementJacobian_in,
               9,
               7,
               &buffer1[0][0]);

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 7; j++)
    {
      if (i == j)
      {
        buffer2[i][j] = 1 - buffer1[i][j];
      }
      else
      {
        buffer2[i][j] = -buffer1[i][j];
      }
    }
  }

  GMath_matMul(&buffer2[i][j],
               7,
               7,
               p_errorCovariance_inout,
               7,
               7,
               p_updatedErrorCovarianceBuffer_in);

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 7; j++)
    {
      *(p_errorCovariance_inout + 7 * i + j) =
          *(p_updatedErrorCovarianceBuffer_in + 7 * i + j);
    }
  }

  return GCONST_TRUE;
}