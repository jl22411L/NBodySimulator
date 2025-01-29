/*
 *    @File:         SunSensor_archiveData.c
 *
 *    @Brief:        File which contains the function declaration for writing
 *                   data of the sun sensor.
 *
 *    @Date:         11/11/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int SunSensor_archiveData(SunSensor_State *p_sunSensor_state_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Add value true value to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_sunSensor_state_in->sunSensorArchive),
                    p_sunSensor_state_in->trueSunVector_Sensor_m[i]);
  }

  /* Add albedo component to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_sunSensor_state_in->sunSensorArchive),
                    p_sunSensor_state_in->albedoComponentNoise_Sensor_m[i]);
  }

  /* Add noise component to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_sunSensor_state_in->sunSensorArchive),
                    p_sunSensor_state_in->noiseVector_Sensor_m[i]);
  }

  /* Add measured value to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_sunSensor_state_in->sunSensorArchive),
                    p_sunSensor_state_in->measuredSunVector_Sensor_m[i]);
  }

  /* Add flag to show if sun sensor is blocked to archive */
  GArchive_addVal(&(p_sunSensor_state_in->sunSensorArchive),
                  p_sunSensor_state_in->isSensorBlockedFlag);

  /* Write data to archive */
  GArchive_writeLine(&(p_sunSensor_state_in->sunSensorArchive));

  return GCONST_TRUE;
}