/*!
 *    @File:         ContinuousEkf_stateEstimation.c
 *
 *    @Brief:        Private function definition for EKF to update the state
 *                   estimation.
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

int ContinuousEkf_stateCorrection(double *p_kalmanGain_in,
                                  double *p_sensorMeasurement_in,
                                  double *p_measurementEstimation_in,
                                  double *p_stateJacobian_in,
                                  uint8_t ekfOrderN_in,
                                  uint8_t ekfDegreeM_in,
                                  double *p_stateCorrection_inout)
{
  /* Declare local variables */
  uint8_t i;
  uint8_t j;

  /*!
   * Find the correction to state from Kalman Gain and store in state correction
   * vector. Later, the current state will be added.
   */
  for (i = 0; i < ekfOrderN_in; i++)
  {
    for (j = 0; j < ekfDegreeM_in; j++)
    {
      *(p_stateCorrection_inout + i) +=
          (*(p_kalmanGain_in + ekfDegreeM_in * i + j)) *
          (*(p_sensorMeasurement_in + j) - *(p_measurementEstimation_in + j));
    }
  }

  return GCONST_TRUE;
}