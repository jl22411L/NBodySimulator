/*!
 *    @File:         JamSail_initAttitudeDetermination.c
 *
 *    @Brief:        Private function definition for initilizing the EKF
 *
 *    @Date:         08/03/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int JamSail_initAttitudeDetermination(JamSail_State  *p_jamSail_state_out,
                                      JamSail_Params *p_jamSail_params_out)
{
  /* Declare local variables */
  dictionary   *p_dic;
  char          parameterBuffer[64];
  GParser_State GParser_state;
  uint8_t       i;

  /* Clear Variables */
  GZero(&GParser_state, GParser_State);
  GZero(&parameterBuffer, char[64]);
  p_dic = NULL;

  /* Load parameters */
  p_dic = GParser_loadParams(&GParser_state, "Parameters/JamSail.ini");

  /* Check that the parameters from the sensor have been loaded */
  if (p_dic == NULL)
  {
    GError("Failed to load parameters for Gyro: %s", "Parameters/JamSail.ini");
  }

  /* Load parameters for EKF system noise covariance matricies */
  for (i = 0; i < 7; i++)
  {
    /* Load name of parameter into buffer */
    sprintf(&(parameterBuffer[0]),
            "EkfProperties:systemNoiseCovariance[%d][%d]",
            i,
            i);

    /* Load parameter into member of JamSails params struct */
    GParser_loadDouble(&GParser_state,
                       p_dic,
                       &(p_jamSail_params_out->systemNoiseCovariance[i][i]),
                       &(parameterBuffer[0]));

    /* Clear buffer */
    GZero(&parameterBuffer, char[64]);
  }

  /* Load parameters for EKF sensor noise covariance matricies */
  for (i = 0; i < 3; i++)
  {
    /* Load name of parameter into buffer */
    sprintf(&(parameterBuffer[0]),
            "EkfProperties:estimationEkfSensorNoiseCovariance[%d][%d]",
            i,
            i);

    /* Load parameter into member of JamSails params struct */
    GParser_loadDouble(
        &GParser_state,
        p_dic,
        &(p_jamSail_params_out->estimationEkfSensorNoiseCovariance[i][i]),
        &(parameterBuffer[0]));

    /* Clear buffer */
    GZero(&parameterBuffer, char[32]);
  }

  /* Set initial condition of quaternion. (All other elements are zero) */
  (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]) = 1.0;

  /* Set initial condition for error covariance */
  for (i = 0; i < JAMSAIL_EKF_ORDER_N; i++)
  {
    p_jamSail_state_out->errorCovariance[i][i] = 1.0;
  }

  /* Load the measurement jacobian matrix for the EKF with coefficient */
  for (i = 0; i < JAMSAIL_ESTIMATION_EKF_DEGREE_M; i++)
  {
    (p_jamSail_state_out->estimationEkfMeasurementJacobian[i][i + 4]) = 1.0;
  }

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  /* Initialze archive */
  GArchive_init(&p_jamSail_state_out->attitudeDeterminationArchive,
                "Bodies/JamSail/ArchiveData/attitudeDetermination");

  /* Add column */
  GArchive_addCol(&p_jamSail_state_out->attitudeDeterminationArchive,
                  "quaternionEstimate_InertCenToBod",
                  4,
                  1);

  /* Add column */
  GArchive_addCol(&p_jamSail_state_out->attitudeDeterminationArchive,
                  "angularVelocityEstimate_Bod_rads",
                  3,
                  1);

  /* Add column */
  GArchive_addCol(&p_jamSail_state_out->attitudeDeterminationArchive,
                  "attitudeMeasuredFlag",
                  1,
                  1);

  /* Write header for archive */
  GArchive_writeHeader(&p_jamSail_state_out->attitudeDeterminationArchive);

  return GCONST_TRUE;
}