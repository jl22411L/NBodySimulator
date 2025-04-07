/*!
 *    @File:         Magnetorquer_createArchives.c
 *
 *    @Brief:        Function which will create archives for the magnetorquer.
 *
 *    @Date:         10/02/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_ParamsStruct.h"
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"

/* Data include */
#include "Actuators/Magnetorquer/ConstantDefs/Magnetorquer_Constants.h"

/* Generic Libraries */
#include "GArchive/Garchive.h"
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Magnetorquer_createArchives(Magnetorquer_Params *p_magnetorquer_params_in,
                                Magnetorquer_State  *p_magnetorquer_state_in,
                                const char          *p_sensorBody_in)
{
  /* Declare local variables */
  char filenameBuffer[MAGNETORQUER_MAX_SENSOR_NAME_BUFFER];

  /* Clear Buffers */
  GZero(&filenameBuffer[0], char[MAGNETORQUER_MAX_SENSOR_NAME_BUFFER]);

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
            p_magnetorquer_params_in->magnetorquerName);
  }
  else
  {
    sprintf(filenameBuffer,
            "Bodies/%s/ArchiveData/%s",
            p_sensorBody_in,
            p_magnetorquer_params_in->magnetorquerName);
  }

  /* Init archive */
  GArchive_init(&p_magnetorquer_state_in->magnetorquerArchive,
                &filenameBuffer[0]);

  /* Add columns for input currents of magnetorquer */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "inputCurrent_Sen_A",
                  3,
                  1);

  /* Add columns for input currents of magnetorquer */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "dipoleMoment_Sen_GAm2",
                  3,
                  1);

  /* Add columns for external magnetic field of magnetorquer */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "externalMagneticField_Sen_nT",
                  3,
                  1);

  /* Add columns for true magnetic torque */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "trueMagnetorquerTorque_Sen_Nm",
                  3,
                  1);

  /* Add columns which represent the noise of the magnetorquer */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "systemNoiseTorque_Sen_Nm",
                  3,
                  1);

  /* Add columns which represent the total torque in sensor frame */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "totalTorque_Sen_Nm",
                  3,
                  1);

  /* Add columns which represent the total torque in body frame */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "totalTorque_Bod_Nm",
                  3,
                  1);

  /* Add columns which represent the total torque in fix frame */
  GArchive_addCol(&p_magnetorquer_state_in->magnetorquerArchive,
                  "totalTorque_Fix_Nm",
                  3,
                  1);

  /* Write the header of the archive */
  GArchive_writeHeader(&p_magnetorquer_state_in->magnetorquerArchive);

  return GCONST_TRUE;
}