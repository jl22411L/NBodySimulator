/*!
 *    @File:         JamSail_attitudeMeasurement.c
 *
 *    @Brief:        Private function which performs attitude measurement for
 *                   JamSail.
 *
 *    @Date:         07/03/2025
 *
 */

/* Function Includes */
#include "Guidance/TriadAlgorithm/PublicFunctions/TriadAlgorithm_PublicFunctions.h"

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int JamSail_attitudeMeasurement(JamSail_State  *p_jamSail_state_inout,
                                JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  double magneticField_Bod_nT[3];
  double magneticField_InertCen_nT[3];
  double sunVector_Bod_nT[3];
  double sunVector_InertCen_nT[3];

  /* Clear Variables */
  GZero(&magneticField_Bod_nT[0], double[3]);
  GZero(&magneticField_InertCen_nT[0], double[3]);
  GZero(&sunVector_Bod_nT[0], double[3]);
  GZero(&sunVector_InertCen_nT[0], double[3]);

  /* Find magnetic field in body frame */
  // TODO

  /* Find magnetic field in Inertical Centric frame */
  // TODO

  /* Find Sun vector in body frame */
  // TODO

  /* Find Sun vector in Inertial Centric Frame */
  // TODO

  /* Apply TRIAD algorithm to determine attitude */
  TriadAlgorithm_getQuat(
      &sunVector_Bod_nT[0],
      &sunVector_InertCen_nT[0],
      &magneticField_Bod_nT[0],
      &magneticField_InertCen_nT[0],
      &(p_jamSail_state_inout->quaternionEstimate_InertCenToBod[0]));

  return GCONST_TRUE;
}