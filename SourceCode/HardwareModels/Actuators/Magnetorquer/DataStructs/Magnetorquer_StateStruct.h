/*!
 *    @File:         Magnetorquer_StateStruct.h
 *
 *    @Brief:        Header file which contains the struct declaration of the
 *                   Magnetorquer State struct.
 *
 *    @Date:         10/02/2025
 *
 */

#ifndef H_MAGNETORQUER_STATESTRUCT_H
#define H_MAGNETORQUER_STATESTRUCT_H

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

typedef struct Magnetorquer_StateStruct
{
  /*!
   * @brief       Input current to magnetorquer, which will be used to find the
   *              dipole moment.
   *
   * @frame       Sensor Frame
   * @units       Amperes
   */
  double inputCurrent_Sen_A[3];

  /*!
   * @brief       Dipole moment of the coils. The reason the units are in
   *              Giga Am^2 is so that they can cell out the nano in nano
   *              teslas.
   *
   * @frame       Sensor Frame
   * @units       Giga Ampers - Meters Squared
   */
  double dipoleMoment_Sen_GAm2[3];

  /*!
   * @brief       Magnetic field experienced by the Magnetorquer which will
   *              interact with the magnetorquer to cause a moment on the body.
   *
   * @frame       Sensor Frame
   * @units       nT
   */
  double externalMagneticField_Sen_nT[3];

  /*!
   * @brief       Noise caused to the external magnetic field.
   *
   * @frame       Sensor Frame
   * @units       nT
   */
  double externalMagneticFieldNoise_Sen_nT[3];

  /*!
   * @brief       True torque that is expected from the actuator, excluding any
   *              system noise.
   *
   * @frame       Sensor Frame
   * @units       Amperes
   */
  double trueMagnetorquerTorque_Sen_Nm[3];

  /*!
   * @brief       System noise in torque
   *
   * @frame       Sensor Frame
   * @units       Newton meters
   */
  double systemNoiseTorque_Sen_Nm[3];

  /*!
   * @brief       Total torque applied by the magnetorquer in sensor frame.
   *
   * @frame       Sensor Frame
   * @units       Newton meters
   */
  double totalTorque_Sen_Nm[3];

  /*!
   * @brief       Total torque applied by the magnetorquer in body frame.
   *
   * @frame       Sensor Frame
   * @units       Newton meters
   */
  double totalTorque_Bod_Nm[3];

  /*!
   * @brief       Total torque applied by the magnetorquer in fixed frame.
   *
   * @frame       Sensor Frame
   * @units       Newton meters
   */
  double totalTorque_Fix_Nm[3];

  /*!
   * @brief     Archive member for actuator.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive magnetorquerArchive;

} Magnetorquer_State;

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETORQUER_STATESTRUCT_H */