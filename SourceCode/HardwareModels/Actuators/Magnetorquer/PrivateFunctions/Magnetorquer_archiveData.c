/*!
 *    @File:         Magnetorquer_archiveData.c
 *
 *    @Brief:        File containing function definition for archiving data of
 *                   magnetorquer
 *
 *    @Date:         10/02/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Actuators/Magnetorquer/DataStructs/Magnetorquer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int Magnetorquer_archiveData(Magnetorquer_State *p_magnetorquer_state_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Archive true magnetic field measuement */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->inputCurrent_Sen_A[i]);
  }

  /* Archive dipole moment */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->dipoleMoment_Sen_Am2[i]);
  }

  /* Archive external magnetic field noise */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->externalMagneticField_Sen_nT[i]);
  }

  /* Archive true torque */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->trueMagnetorquerTorque_Sen_Nm[i]);
  }

  /* Archive system noise of magnetorquer */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->systemNoiseTorque_Sen_Nm[i]);
  }

  /* Archive total torque in sensor frame */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->totalTorque_Sen_Nm[i]);
  }

  /* Archive total torque in body frame */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->totalTorque_Bod_Nm[i]);
  }

  /* Archive total torque in fix frame */
  for (i = 0; i < 3; i++)
  {
    GArchive_addVal(&(p_magnetorquer_state_in->magnetorquerArchive),
                    p_magnetorquer_state_in->totalTorque_Fix_Nm[i]);
  }

  /* Write data to archive */
  GArchive_writeLine(&(p_magnetorquer_state_in->magnetorquerArchive));

  return GCONST_TRUE;
}