/*
 *    @File:         Igrf_loadParams.c
 *
 *    @Brief:
 *
 *    @Date:         21/10/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Igrf_loadParams(Igrf_Params *p_igrf_params_out,
                    const char  *p_paramsFilePath_in,
                    uint8_t      nMaxDegree_in,
                    uint8_t      igrfIteration_in)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  char          parameterNameBuffer[IGRF_MAX_STRING_BUFFER_SIZE];
  uint8_t       n;
  uint8_t       m;

  /* Clear the Igrf Params Struct */
  GZero(&GParser_state, GParser_State);
  GZero(p_igrf_params_out, Igrf_Params);
  p_dic = NULL;

  /* Loading parameters into dictionaries */
  p_dic = GParser_loadParams(&GParser_state, p_paramsFilePath_in);

  /* If nMaxDegree_in is not within a valid range, raise an error */
  if (!(1 <= nMaxDegree_in && nMaxDegree_in <= IGRF_MAX_DEGREE))
  {
    GError("nMaxDegree = %d, which is outside the valid range of 1 <= "
           "nMaxDegree <= 13 ",
           nMaxDegree_in);
  }

  /* Load the IGRF iteration number into the struct */
  p_igrf_params_out->igrfIteration = igrfIteration_in;

  /* Load max degree of the legendre polynomials into the IGRF params struct */
  p_igrf_params_out->nMaxDegree = nMaxDegree_in;

  /* ------------------------------------------------------------------------ *
   * LOAD PARAMETERS INTO STRUCT
   * ------------------------------------------------------------------------ */

  /* -------------------------- LOAD TIME VARIABLES ------------------------- */

  /* Clear the parameter name buffer */
  GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

  /* Write the name of the parameter to load into buffer */
  sprintf(&parameterNameBuffer[0], "igrf%d:unixStartTime_s", igrfIteration_in);

  /* Load start time parameter */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &p_igrf_params_out->startUnixTime_s,
                     &parameterNameBuffer[0]);

  /* Clear the parameter name buffer */
  GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

  /* Write the name of the parameter to load into buffer */
  sprintf(&parameterNameBuffer[0], "igrf%d:unixEndTime_s", igrfIteration_in);

  /* Load end time parameter */
  GParser_loadDouble(&GParser_state,
                     p_dic,
                     &p_igrf_params_out->endUnixTime_s,
                     &parameterNameBuffer[0]);

  /* --------------------- LOAD COEFFICIENTS VARIABLES ---------------------- */

  /* Iterate through dictionary and load coefficients */
  for (n = 1; n <= nMaxDegree_in; n++)
  {
    for (m = 0; m <= n; m++)
    {
      /* --------------------------- EPOCH VALUES --------------------------- */

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(&parameterNameBuffer[0],
              "igrf%d:igrf%d_epochValue_g_n%d_m%d",
              igrfIteration_in,
              igrfIteration_in,
              n,
              m);

      /* Load coefficient into array */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &p_igrf_params_out->gEpochCoefficients_nT[n][m],
                         &parameterNameBuffer[0]);

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(&parameterNameBuffer[0],
              "igrf%d:igrf%d_epochValue_h_n%d_m%d",
              igrfIteration_in,
              igrfIteration_in,
              n,
              m);

      /* Load coefficient into array */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &p_igrf_params_out->hEpochCoefficients_nT[n][m],
                         &parameterNameBuffer[0]);

      /* --------------------------- LINEAR RATES --------------------------- */

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(&parameterNameBuffer[0],
              "igrf%d:igrf%d_linearRate_g_n%d_m%d",
              igrfIteration_in,
              igrfIteration_in,
              n,
              m);

      /*!
       * Load coefficient into array.
       *
       * Note: The coefficients are first loaded with the units nT per year.
       *       they are then converted to nT per second. This is done for
       *        simplicity.
       */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &p_igrf_params_out->gLinearRateCoefficients_nTs[n][m],
                         &parameterNameBuffer[0]);

      /* Convert coefficient to seconds */
      p_igrf_params_out->gLinearRateCoefficients_nTs[n][m] /=
          GCONST_YEARS_TO_SECONDS_CONVERSION;

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(&parameterNameBuffer[0],
              "igrf%d:igrf%d_linearRate_h_n%d_m%d",
              igrfIteration_in,
              igrfIteration_in,
              n,
              m);

      /*!
       * Load coefficient into array.
       *
       * Note: The coefficients are first loaded with the units nT per year.
       *       they are then converted to nT per second. This is done for
       *        simplicity.
       */
      GParser_loadDouble(&GParser_state,
                         p_dic,
                         &p_igrf_params_out->hLinearRateCoefficients_nTs[n][m],
                         &parameterNameBuffer[0]);

      /* Convert coefficient to seconds */
      p_igrf_params_out->hLinearRateCoefficients_nTs[n][m] /=
          GCONST_YEARS_TO_SECONDS_CONVERSION;
    }
  }

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  return GCONST_TRUE;
}
