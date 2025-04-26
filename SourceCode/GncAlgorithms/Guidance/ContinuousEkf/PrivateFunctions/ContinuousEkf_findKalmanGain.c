/*!
 *    @File:         ContinuousEkf_findKalmanGain.c
 *
 *    @Brief:        Private Function definition for computing the EKF Kalman
 *                   gain.
 *
 *    @Date:         04/03/2025
 *
 */

#include <stdint.h>
#include <stdio.h> // REMOVE

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

int ContinuousEkf_findKalmanGain(double *p_intermediateKalmanGain_in,
                                 double *p_measurementJacobian_in,
                                 double *p_sensorNoiseCovariance_in,
                                 double *p_errorCovariance_in,
                                 uint8_t ekfOrderN_in,
                                 uint8_t ekfDegreeM_in,
                                 double *p_kalmanGain_out)
{
  /* Declare local variables */
  double  intermediateKalmanGain[9][9];
  double  buffer1[9][7];
  double  buffer2[7][9];
  double  buffer3[9][9];
  double  buffer4[9][9];
  double  buffer5[7][9];
  uint8_t i;
  uint8_t j;

  /* Clear variables */
  GZero(&intermediateKalmanGain[0][0], double[9][9]);
  GZero(&buffer1[0][0], double[9][9]);
  GZero(&buffer2[0][0], double[7][9]);
  GZero(&buffer3[0][0], double[9][9]);
  GZero(&buffer4[0][0], double[9][9]);
  GZero(&buffer5[0][0], double[7][9]);

  GMath_matMul(p_measurementJacobian_in,
               9,
               7,
               p_errorCovariance_in,
               7,
               7,
               &buffer1[0][0]);

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 9; j++)
    {
      buffer2[i][j] = *(p_measurementJacobian_in + 7 * j + i);
    }
  }

  GMath_matMul(&buffer1[0][0], 9, 7, &buffer2[0][0], 7, 9, &buffer3[0][0]);

  for (i = 0; i < 9; i++)
  {
    for (j = 0; j < 9; j++)
    {
      buffer3[i][j] += *(p_sensorNoiseCovariance_in + 9 * i + j);
    }
  }

  GMath_invMat(&buffer3[0][0], &buffer4[0][0], 9);

  GMath_matMul(&buffer2[0][0], 7, 9, &buffer4[0][0], 9, 9, &buffer5[0][0]);

  GMath_matMul(p_errorCovariance_in,
               7,
               7,
               &buffer5[0][0],
               7,
               9,
               p_kalmanGain_out);

  return GCONST_TRUE;
}