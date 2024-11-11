/*
 *    @File:         SunSensor_createArchives.c
 *
 *    @Brief:        Private function which will init the arhive for the Sun
 *                   Sensor.
 *
 *    @Date:         11/11/2024
 *
 */

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_Params.h"
#include "SunSensor/DataStructs/SunSensor_State.h"

/* Data include */
#include "SunSensor/ConstantDefs/SunSensor_ConstDefs.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int SunSensor_createArchives(SunSensor_Params *p_sunSensor_params_in,
                             SunSensor_State  *p_sunSesor_state_in,
                             const char       *p_sensorBody_in)
{
  /* Declare local variables */
  char filenameBuffer[SUNSENSOR_ARCHIVE_FILENAME_BUFFER];

  /* Clear Buffers */
  GZero(&filenameBuffer[0], char[SUNSENSOR_ARCHIVE_FILENAME_BUFFER]);

  /*!
   * Create the directory to where the archive will be saved. If the string is
   * of length 0, then it is assumed that the sensor does not belong to a body
   * and hence the archive is saved to the top level Archive folder of the
   * test run.
   */
  if (strlen(p_sensorBody_in) == 0)
  {
    sprintf(filenameBuffer,
            "Bodies/%s/ArchiveData/%s",
            p_sensorBody_in,
            p_sunSensor_params_in->sunSensorName);
  }
  else
  {
    sprintf(filenameBuffer,
            "ArchiveData/%s",
            p_sunSensor_params_in->sunSensorName);
  }

  /* Init archive */
  GArchive_init(&p_sunSesor_state_in->sunSensorArchive, &filenameBuffer[0]);

  /* Add columns for true value of sun vector */
  GArchive_addCol(&p_sunSesor_state_in->sunSensorArchive,
                  "trueSunVector_Bod_m",
                  1,
                  3);

  /* Add columns for noise vector od sensor */
  GArchive_addCol(&p_sunSesor_state_in->sunSensorArchive,
                  "noiseVector_Bod_m",
                  1,
                  3);

  /* Add columns which represent the measured output of the sensor */
  GArchive_addCol(&p_sunSesor_state_in->sunSensorArchive,
                  "measuredSunVector_Bod_m",
                  1,
                  3);

  /* Write the header of the archive */
  GArchive_writeHeader(&p_sunSesor_state_in->sunSensorArchive);

  return GCONST_TRUE;
}