/*!
 *    @File:         JamSail_ParamsStruct.h
 *
 *    @Brief:        Header file which contains the params struct for JamSail.
 *
 *    @Date:         28/01/2025
 *
 */

#ifndef H_JAMSAIL_PARAMSSTRUCT_H
#define H_JAMSAIL_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Sensors/Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Sensors/SunSensor/DataStructs/SunSensor_ParamsStruct.h"


/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct JamSail_ParamsStruct
{
  /* ------------------------------------------------------------------------ *
   * Satellite Parameters
   * ------------------------------------------------------------------------ */

  /* None */

  /* ------------------------------------------------------------------------ *
   * Sensor Parameters
   * ------------------------------------------------------------------------ */

  /*!
   * @brief     Struct which contains the parameters of the Sun Sensor on
   *            JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  SunSensor_Params sunSensor_params;

  /*!
   * @brief     Struct which contains the parameters of the Magnetometer on
   *            JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  Magnetometer_Params magnetometer_params;

  /*!
   * @brief     Struct which contains the parameters of the Gyro on JamSail.
   *
   * @frame     N/A
   * @unit      N/A
   */
  Gyro_Params gyro_params;

} JamSail_Params;

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_PARAMSSTRUCT_H */