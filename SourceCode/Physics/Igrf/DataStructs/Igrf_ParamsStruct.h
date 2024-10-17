/*
 *    @File:         Igrf_ParamsStruct.h
 *
 *    @Brief:        Contains the params struct for the IGRF model
 *
 *    @Date:         11/09/2024
 *
 */

#ifndef H_IGRF_PARAMSSTRUCT_H
#define H_IGRF_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
/* None */

typedef struct Igrf_ParamsStruct
{

  /*!
   * @brief     The degree at which the Igrf model is being used
   *
   * @frame N/A
   * @unit  N/A
   */
  uint8_t nDegree;

  /*!
   * @brief     Find the epoch year for the IGRF model. This should be using
   *            standard calender time.
   *
   * @frame N/A
   * @unit  year
   */
  uint16_t epochYear;

  /*!
   * @brief     Contains the g Coefficients for the Igrf model at the epoch
   *            time.
   *
   * @frame     N/A
   * @unit      nT
   */
  double gEpochCoefficients_nT[IGRF_MAX_COEFFICIENTS][IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the linear rate gCoefficients for the Igrf model. This
   *            is used to interpolate what the gCoefficient is at the a certain
   *            time.
   *
   * @frame     N/A
   * @unit      nT per s
   */
  double gLinearRateCoefficients_nTs[IGRF_MAX_COEFFICIENTS]
                                    [IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the h Coefficients for the Igrf model at the epoch
   *            time.
   *
   * @frame     N/A
   * @unit      nT
   */
  double hEpochCoefficients_nT[IGRF_MAX_COEFFICIENTS][IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the linear rate hCoefficients for the Igrf model. This
   *            is used to interpolate what the hCoefficient is at the a certain
   *            time.
   *
   * @frame     N/A
   * @unit      nT per second
   */
  double hLinearRateCoefficients_nTs[IGRF_MAX_COEFFICIENTS]
                                    [IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Array which contains the quasi-normalization factors
   *
   * @frame     N/A
   * @unit      N/A
   */
  double schmidtQuasiNormalisationFunctions[IGRF_MAX_COEFFICIENTS]
                                           [IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Array which contains the quasi-normalization derivitive factors
   *
   * @frame     N/A
   * @unit      N/A
   */
  double schmidtQuasiNormalisationDerivitiveFunctions[IGRF_MAX_COEFFICIENTS]
                                                     [IGRF_MAX_COEFFICIENTS];

} Igrf_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PARAMSSTRUCT_H */
