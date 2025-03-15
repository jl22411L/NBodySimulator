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
  uint8_t i;
  uint8_t j;
  uint8_t k;
  uint8_t l;

  /* Clear variables */
  GZero(p_updatedErrorCovarianceBuffer_in, double[ekfOrderN_in][ekfOrderN_in]);

  /*!
   * Update the error covariance matrix.
   *
   * This essentially performs the matrix operation:
   *          P_updated = P - K*H*P
   *          (which is the expanded form of the equation (P = (I-K*H*P)))
   *
   * The reason it has 4 for loops is this acts as a custom matrix multiplier.
   * WHile the 4 for loops is bad practice it does work and does remove the need
   * for having a buffer or dynamically allocating memory.
   *
   * TODO: It may be possible to put the k & l for loop into its own function,
   *       taking i & j as input parameters. This would clean up the code and
   *       make it easier to follow.
   */
  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      for (k = 0; k < ekfDegreeM_in; k++)
      {
        for (l = 0; l < ekfOrderN_in; l++)
        {
          *(p_updatedErrorCovarianceBuffer_in + ekfOrderN_in * i + j) -=
              (*(p_kalmanGain_in + ekfDegreeM_in * i + k)) *
              (*(p_measurementJacobian_in + ekfOrderN_in * k + l)) *
              (*(p_errorCovariance_inout + ekfOrderN_in * l + j));
        }
      }

      *(p_updatedErrorCovarianceBuffer_in + ekfOrderN_in * i + j) +=
          *(p_errorCovariance_inout + ekfOrderN_in * i + j);
    }
  }

  /* Replace the values in the error covariance with the updated covariance */
  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      *(p_errorCovariance_inout + ekfOrderN_in * i + j) =
          *(p_updatedErrorCovarianceBuffer_in + ekfOrderN_in * i + j);
    }
  }

  return GCONST_TRUE;
}