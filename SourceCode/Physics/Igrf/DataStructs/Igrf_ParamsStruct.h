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
   * @brief     Unisgned integer which contains the iteration number of the
   *            IGRF model that is loaded into the parameters structs.
   *
   *            ...
   *            Iteration 12: 2015 - 2020
   *            Iteration 13: 2020 - 2025
   *            ...
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t igrfIteration;

  /*!
   * @brief     Unix time for start of generation.
   *
   * @frame     N/A
   * @unit      s
   */
  double startUnixTime_s;

  /*!
   * @brief     Unix time for end of generation.
   *
   * @frame     N/A
   * @unit      s
   */
  double endUnixTime_s;

  /*!
   * @brief     Unsigned integer which contains the maximum degree which is
   *            being used for the IGRF model.
   *
   * @frame     N/A
   * @unit      N/A
   */
  uint8_t nMaxDegree;

  /*!
   * @brief     Contains the g Coefficients for the Igrf model at the epoch
   *            time.
   *
   *            NOTE: The +1 is so the index of the elemen will match with the
   *                  degree and order that is present in the literature.
   *
   * @frame     N/A
   * @unit      nT
   */
  double gEpochCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];

  /*!
   * @brief     Contains the linear rate gCoefficients for the Igrf model. This
   *            is used to interpolate what the gCoefficient is at the a certain
   *            time.
   *
   *            NOTE: The +1 is so the index of the elemen will match with the
   *                  degree and order that is present in the literature.
   *
   * @frame     N/A
   * @unit      nT per s
   */
  double gLinearRateCoefficients_nTs[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];

  /*!
   * @brief     Contains the h Coefficients for the Igrf model at the epoch
   *            time.
   *
   *            NOTE: The +1 is so the index of the elemen will match with the
   *                  degree and order that is present in the literature.
   *
   * @frame     N/A
   * @unit      nT
   */
  double hEpochCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];

  /*!
   * @brief     Contains the linear rate hCoefficients for the Igrf model. This
   *            is used to interpolate what the hCoefficient is at the a certain
   *            time.
   *
   *            NOTE: The +1 is so the index of the elemen will match with the
   *                  degree and order that is present in the literature.
   *
   * @frame     N/A
   * @unit      nT per second
   */
  double hLinearRateCoefficients_nTs[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];

} Igrf_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PARAMSSTRUCT_H */
