/*!
 *    @File:         Gyro_createArchives.c
 *
 *    @Brief:        Function which creates archives for Gyro model.
 *
 *    @Date:         05/02/2025
 *
 */

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Sensors/Gyro/DataStructs/Gyro_ParamsStruct.h"
#include "Sensors/Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
#include "Sensors/Gyro/ConstantDefs/Gyro_ConstansDefs.h"

/* Generic Libraries */
#include "GArchive/Garchive.h"
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Gyro_createArchives(Gyro_Params *p_gyro_params_in,
                        Gyro_State  *p_gyro_state_in,
                        const char  *p_sensorBody_in)
{
  /* Declare local variables */
  char filenameBuffer[GYRO_ARCHIVE_FILENAME_BUFFER];

  /* Clear Buffers */
  GZero(&filenameBuffer[0], char[GYRO_ARCHIVE_FILENAME_BUFFER]);

  /*!
   * Create the directory to where the archive will be saved. If the string is
   * of length 0, then it is assumed that the sensor does not belong to a body
   * and hence the archive is saved to the top level Archive folder of the
   * test run.
   */
  if (strlen(p_sensorBody_in) == 0)
  {
    sprintf(filenameBuffer, "ArchiveData/%s", p_gyro_params_in->gyroName);
  }
  else
  {
    sprintf(filenameBuffer,
            "Bodies/%s/ArchiveData/%s",
            p_sensorBody_in,
            p_gyro_params_in->gyroName);
  }

  /* Init archive */
  GArchive_init(&p_gyro_state_in->gyroArchive, &filenameBuffer[0]);

  /* Add columns for true value of sun vector */
  GArchive_addCol(&p_gyro_state_in->gyroArchive,
                  "trueGyroVector_Sen_rads",
                  3,
                  1);

  /* Add columns for albedo effects of sun vector */
  GArchive_addCol(&p_gyro_state_in->gyroArchive,
                  "noiseGyroVector_Sen_rads",
                  3,
                  1);

  /* Add columns which represent the measured output of the sensor */
  GArchive_addCol(&p_gyro_state_in->gyroArchive,
                  "measuredGyroVector_Sen_rads",
                  3,
                  1);

  /* Add columns which represent the measured output of the sensor */
  GArchive_addCol(&p_gyro_state_in->gyroArchive,
                  "filteredGyroVector_Sen_rads",
                  3,
                  1);

  /* Write the header of the archive */
  GArchive_writeHeader(&p_gyro_state_in->gyroArchive);

  return GCONST_TRUE;
}