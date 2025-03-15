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
  uint8_t       j;

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
  for (i = 0; i < JAMSAIL_EKF_ORDER_N; i++)
  {
    for (j = 0; j < JAMSAIL_EKF_ORDER_N; j++)
    {
      /* Load name of parameter into buffer */
      sprintf(&(parameterBuffer[0]),
              "EkfProperties:systemNoiseCovariance[%d][%d]",
              i,
              j);

      /* Load parameter into member of JamSails params struct */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &(p_jamSail_params_out->systemNoiseCovariance[i][j]),
                         &(parameterBuffer[0]));

      /* Clear buffer */
      GZero(&parameterBuffer, char[64]);
    }
  }

  /* Load parameters for EKF sensor noise covariance matricies */
  for (i = 0; i < JAMSAIL_EKF_DEGREE_M; i++)
  {
    for (j = 0; j < JAMSAIL_EKF_DEGREE_M; j++)
    {
      /* Load name of parameter into buffer */
      sprintf(&(parameterBuffer[0]),
              "EkfProperties:sensorNoiseCovariance[%d][%d]",
              i,
              j);

      /* Load parameter into member of JamSails params struct */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &(p_jamSail_params_out->sensorNoiseCovariance[i][j]),
                         &(parameterBuffer[0]));

      /* Clear buffer */
      GZero(&parameterBuffer, char[32]);
    }
  }

  /* Set initial condition of quaternion. (All other elements are zero) */
  (p_jamSail_state_out->quaternionEstimate_InertCenToBod[3]) = 1.0;

  /* Set initial condition for error covariance */
  for (i = 0; i < JAMSAIL_EKF_ORDER_N; i++)
  {
    p_jamSail_state_out->errorCovariance[i][i] = 1.0;
  }

  /* ------------------------------------------------------------------------ *
   * KEPLARIAN ELEMENTS
   * ------------------------------------------------------------------------ */

  /* Load semi major axis */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->semiMajorAxis_km),
                     "OrbitalElements:semiMajorAxis_km");

  /* Load eccentricity */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->eccentricity),
                     "OrbitalElements:eccentricity");

  /* Load inclination */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->inclination_rad),
                     "OrbitalElements:inclination_rad");

  /* Load argument of periapsis */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->argumentOfPerigee_rad),
                     "OrbitalElements:argumentOfPerigee_rad");

  /* Load RAANS */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->raans_rad),
                     "OrbitalElements:raans_rad");

  /* Load time since periapsis */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->timeSincePeriapsis_s),
                     "OrbitalElements:timeSincePeriapsis_s");

  /* Load earth mass parameter */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->earthMass_kg),
                     "EarthProperties:earthMass_kg");

  /* Load earth side real time parameter */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->earthSideRealTime_s),
                     "EarthProperties:earthSideRealTime_s");

  /* Find average rotaional speed of the earth */
  (p_jamSail_params_out->averageEarthRotationalSpeedMag_rads) =
      2 * GCONST_PI / (p_jamSail_params_out->earthSideRealTime_s);

  /* Load earth side real time parameter */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &(p_jamSail_params_out->earthEqutorialRadius_m),
                     "EarthProperties:earthEqutorialRadius_m");

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