/*!
 *    @File:         Magnetometer_archiveData.c
 *
 *    @Brief:        Function which wil archive data relating to magnetometer.
 *
 *    @Date:         04/02/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Sensors/Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int Magnetometer_archiveData(Magnetometer_State *p_magnetometer_state_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Archive true magnetic field measuement */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &(p_magnetometer_state_in->magnetometerArchive),
        p_magnetometer_state_in->trueMagneticFieldMeasurement_Sen_nT[i]);
  }

  /* Archive external magnetic field noise */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &(p_magnetometer_state_in->magnetometerArchive),
        p_magnetometer_state_in->externalMagneticFieldNoise_Sen_nT[i]);
  }

  /* Archive magnetic field sensor noise */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(
        &(p_magnetometer_state_in->magnetometerArchive),
        p_magnetometer_state_in->sensorMagneticFieldNoise_Sen_nT[i]);
  }

  /* Archive measured magnetic field */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetometer_state_in->magnetometerArchive),
                    p_magnetometer_state_in->measuredMagneticField_Sen_nT[i]);
  }

  /* Archive measured magnetic field */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetometer_state_in->magnetometerArchive),
                    p_magnetometer_state_in->filteredMagneticField_Sen_nT[i]);
  }

  /* Write data to archive */
  GArchive_writeLine(&(p_magnetometer_state_in->magnetometerArchive));

  return GCONST_TRUE;
}