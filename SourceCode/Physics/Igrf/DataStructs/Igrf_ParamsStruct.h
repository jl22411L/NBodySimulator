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
   */
  uint8_t nDegree;

  /*!
   * @brief     Find the epoch year for the IGRF model
   */
  uint16_t epochYear;

  /*!
   * @brief     Contains the g Coefficients for the Igrf model
   *
   * @frame     N/A
   * @unit      N/A
   */
  double gCoefficients[IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the linear rate gCoefficients for the Igrf model
   *
   * @frame     N/A
   * @unit      N/A
   */
  double gLinearRateCoefficients[IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the h Coefficients for the Igrf model
   *
   * @frame     N/A
   * @unit      N/A
   */
  double hCoefficients[IGRF_MAX_COEFFICIENTS];

  /*!
   * @brief     Contains the linear rate h Coefficients for the Igrf model
   *
   * @frame     N/A
   * @unit      N/A
   */
  double hLinearRateCoefficients[IGRF_MAX_COEFFICIENTS];

} Igrf_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PARAMSSTRUCT_H */
