/*!
 *    @File:         Gyro_archiveData.c
 *
 *    @Brief:        Private function which archives data from Gyro model.
 *
 *    @Date:         05/02/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Sensors/Gyro/DataStructs/Gyro_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int Gyro_archiveData(Gyro_State *p_gyro_state_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Add value true value to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_gyro_state_in->gyroArchive),
                    p_gyro_state_in->trueGyroVector_Sen_rads[i]);
  }

  /* Add noise component to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_gyro_state_in->gyroArchive),
                    p_gyro_state_in->noiseGyroVector_Sen_rads[i]);
  }

  /* Add measured value to archive */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_gyro_state_in->gyroArchive),
                    p_gyro_state_in->measuredGyroVector_Sen_rads[i]);
  }

  /* Write data to archive */
  GArchive_writeLine(&(p_gyro_state_in->gyroArchive));

  return GCONST_TRUE;
}