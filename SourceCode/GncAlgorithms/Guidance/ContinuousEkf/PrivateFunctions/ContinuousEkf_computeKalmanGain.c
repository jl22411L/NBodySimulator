/*!
 *    @File:         ContinuousEkf_computeKalmanGain.c
 *
 *    @Brief:        Private Function definition for computing the EKF Kalman
 *                   gain.
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

int ContinuousEkf_computeKalmanGain(double *p_intermediateKalmanGain_in,
                                    double *p_measurementJacobian_in,
                                    double *p_sensorNoiseCovariance_in,
                                    double *p_currentSystemCovariance_in,
                                    uint8_t ekfOrderN_in,
                                    uint8_t ekfDegreeM_in,
                                    double *p_kalmanGain_out)
{
  /* Declare local variables */
  uint8_t i;
  uint8_t k;
  uint8_t l;
  uint8_t j;

  /* Clear Variables */
  GZero(p_intermediateKalmanGain_in, double[ekfDegreeM_in][ekfDegreeM_in]);
  GZero(p_kalmanGain_out, double[ekfOrderN_in][ekfDegreeM_in]);

  /* Find the intermediate matrix of the kalman gain */
  // TODO: Should break two for loops into functions to remove the 4 for loops
  for (i = 0; i < ekfDegreeM_in; i++)
  {
    for (j = 0; j < ekfDegreeM_in; j++)
    {
      for (k = 0; k < ekfOrderN_in; k++)
      {
        for (l = 0; l < ekfOrderN_in; l++)
        {
          *(p_intermediateKalmanGain_in + ekfDegreeM_in * i + j) +=
              (*(p_measurementJacobian_in + ekfDegreeM_in * i + l)) *
              (*(p_currentSystemCovariance_in + ekfOrderN_in * l + k)) *
              (*(p_measurementJacobian_in + ekfDegreeM_in * j + k));
        }
      }

      *(p_intermediateKalmanGain_in + ekfDegreeM_in * i + j) +=
          *(p_sensorNoiseCovariance_in + ekfDegreeM_in * i + j);
    }
  }

  /* Find the inverse of the intermediate kalman gain */
  GMath_invMat(p_intermediateKalmanGain_in,
               p_intermediateKalmanGain_in,
               ekfDegreeM_in);

  /* Find the kalman gain */
  // TODO: Should break two for loops into functions to remove the 4 for loops
  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfDegreeM_in; j++)
    {
      for (k = 0; k < ekfDegreeM_in; k++)
      {
        for (l = 0; l < ekfOrderN_in; l++)
        {
          *(p_kalmanGain_out + ekfDegreeM_in * i + j) +=
              (*(p_currentSystemCovariance_in + ekfOrderN_in * i + l)) *
              (*(p_measurementJacobian_in + ekfOrderN_in * k + l)) *
              (*(p_intermediateKalmanGain_in + ekfOrderN_in * k + j));
        }
      }
    }
  }

  return GCONST_TRUE;
}