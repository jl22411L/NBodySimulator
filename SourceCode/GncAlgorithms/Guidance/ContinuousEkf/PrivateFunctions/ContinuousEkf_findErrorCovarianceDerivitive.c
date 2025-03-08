/*!
 *    @File:         ContinuousEkf_findCovarianceDerivitive.c
 *
 *    @Brief:        Private function definition for finding continuous EKF
 *                   covariance.
 *
 *    @Date:         03/03/2025
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

int ContinuousEkf_findCovarianceDerivitive(
    double *p_stateJacobian_in,
    double *p_errorCovariance_in,
    double *p_systemNoiseCovariance_in,
    uint8_t ekfOrderN_in,
    double *p_errorCovarianceDerivitive_out)
{
  /* Declare local variables */
  uint8_t i;
  uint8_t j;
  uint8_t k;

  /* Clear variables */
  GZero(p_errorCovarianceDerivitive_out, double[ekfOrderN_in][ekfOrderN_in]);

  /*!
   * This is effectively a custom builr matrix multiplier. The equation which is
   * being used to find the covariance derivitive is:
   *
   *    dP = F*P + P*F^T + Q
   *
   * Where, ^T means that the matrix is transpose. Essentially, when multiplying
   * two matricies, you takw the ith row of the first matrix and dot product it
   * with the jth column of the second. When you transpose one of the matricies,
   * you switch the row to a column. Hence, for dealing with the second term
   * in the equation, you take the ith row of P and jth row of F.
   */
  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfOrderN_in; j++)
    {
      for (k = 0; k < ekfOrderN_in; k++)
      {
        *(p_errorCovarianceDerivitive_out + ekfOrderN_in * i + j) +=
            ((*(p_stateJacobian_in + ekfOrderN_in * i + k)) *
                 (*(p_errorCovariance_in + ekfOrderN_in * k + j)) +
             (*(p_errorCovariance_in + ekfOrderN_in * i + k)) *
                 (*(p_stateJacobian_in + ekfOrderN_in * j + k)) +
             *(p_systemNoiseCovariance_in + ekfOrderN_in * i + j));
      }
    }
  }

  return GCONST_TRUE;
}