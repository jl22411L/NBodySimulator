/*!
 *    @File:         Magnetometer_StateStruct.h
 *
 *    @Brief:        Header file which contains the state struct of the
 *                   magnetometer.
 *
 *    @Date:         30/01/2025
 *
 */

#ifndef H_MAGNETOMETER_STATESTRUCT_H
#define H_MAGNETOMETER_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"

typedef struct Magnetometer_StateStruct
{
  /*!
   * @brief     True reading of magnetic field.
   *
   * @frame     Sensor Frame
   * @units     Nano Teslas
   */
  double trueMagneticFieldMeasurement_Sen_nT[3];

  /*!
   * @brief     Magnetic field caused by external sources. Like a magnetorquer
   *            or hardware electronics.
   *
   * @frame     Sensor Frame
   * @units     Nano Teslas
   */
  double externalMagneticFieldNoise_Sen_nT[3];

  /*!
   * @brief     Random noise which is generated withibn the sensor when
   *            measuring the magnetic field.
   *
   * @frame     Sensor Frame
   * @units     Nano Teslas
   */
  double sensorMagneticFieldNoise_Sen_nT[3];

  /*!
   * @brief     The actual reading of the magnetic field by the sensor.
   *
   * @frame     Sensor Frame
   * @units     Nano Teslas
   */
  double measuredMagneticField_Sen_nT[3];

  /*!
   * @brief     Measured vector of the sensor from previous timestep. (Used for
   *            low pass filtering)
   *
   * @frame     Sensor
   * @units     Nano Teslas
   */
  double previousFilteredMagneticField_Sen_nT[3];

  /*!
   * @brief     Filtered vector reading of magnetic field.
   *
   * @frame     Sensor
   * @units     Nano Teslas
   */
  double filteredMagneticField_Sen_nT[3];

  /*!
   * @brief     Archive member for sensor.
   *
   * @frame     N/A
   * @units     N/A
   */
  GArchive magnetometerArchive;

} Magnetometer_State;

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETOMETER_STATESTRUCT_H */