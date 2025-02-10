/*!
 *    @File:         Magnetometer_createArchives.c
 *
 *    @Brief:        Function which will create archives for the magnetometer.
 *
 *    @Date:         30/01/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "Sensors/Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Sensors/Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
#include "Sensors/Magnetometer/ConstantDefs/Magnetometer_ConstDefs.h"

/* Generic Libraries */
#include "GArchive/Garchive.h"
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Magnetometer_createArchives(Magnetometer_Params *p_magnetometer_params_in,
                                Magnetometer_State  *p_magnetometer_state_in,
                                const char          *p_sensorBody_in)
{
  /* Declare local variables */
  char filenameBuffer[MAGNETOMETER_MAX_SENSOR_NAME_BUFFER];

  /* Clear Buffers */
  GZero(&filenameBuffer[0], char[MAGNETOMETER_MAX_SENSOR_NAME_BUFFER]);

  /*!
   * Create the directory to where the archive will be saved. If the string is
   * of length 0, then it is assumed that the sensor does not belong to a body
   * and hence the archive is saved to the top level Archive folder of the
   * test run.
   */
  if (strlen(p_sensorBody_in) == 0)
  {
    sprintf(filenameBuffer,
            "ArchiveData/%s",
            p_magnetometer_params_in->magnetometerName);
  }
  else
  {
    sprintf(filenameBuffer,
            "Bodies/%s/ArchiveData/%s",
            p_sensorBody_in,
            p_magnetometer_params_in->magnetometerName);
  }

  /* Init archive */
  GArchive_init(&p_magnetometer_state_in->magnetometerArchive,
                &filenameBuffer[0]);

  /* Add columns for true value of sun vector */
  GArchive_addCol(&p_magnetometer_state_in->magnetometerArchive,
                  "trueMagneticFieldMeasurement_Sen_nT",
                  3,
                  1);

  /* Add columns for albedo effects of sun vector */
  GArchive_addCol(&p_magnetometer_state_in->magnetometerArchive,
                  "externalMagneticFieldNoise_Sen_nT",
                  3,
                  1);

  /* Add columns for noise vector od sensor */
  GArchive_addCol(&p_magnetometer_state_in->magnetometerArchive,
                  "sensorMagneticFieldNoise_Sen_nT",
                  3,
                  1);

  /* Add columns which represent the measured output of the sensor */
  GArchive_addCol(&p_magnetometer_state_in->magnetometerArchive,
                  "measuredMagneticField_Sen_nT",
                  3,
                  1);

  /* Write the header of the archive */
  GArchive_writeHeader(&p_magnetometer_state_in->magnetometerArchive);

  return GCONST_TRUE;
}