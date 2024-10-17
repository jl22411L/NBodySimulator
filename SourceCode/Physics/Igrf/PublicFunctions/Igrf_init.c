/*
 *    @File:         Igrf_init.c
 *
 *    @Brief:        Initialises the Igrf library by loading all the parameters
 *                   for the model.
 *
 *    @Date:         11/09/2024
 *
 */

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Igrf_init(Igrf_Params *p_igrf_params_out, const char *p_paramsFilePath_in)
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

  /* ------------------------------------------------------------------------ *
   * LOAD PARAMETERS INTO STRUCT
   * ------------------------------------------------------------------------ */

  /* Load the degree which the model will follow */
  GParser_loadUInt8(
      &GParser_state,
      p_dic,
      &p_igrf_params_out->nDegree,
      "modelParameters:nDegree");

  /* Load epoch year of the corresponding coefficients */
  GParser_loadUInt16(
      &GParser_state,
      p_dic,
      &p_igrf_params_out->epochYear,
      "modelParameters:epochYear");

  /* Iterate through dictionary and load coefficients */
  for (n = 1; n <= p_igrf_params_out->nDegree; n++)
  {
    for (m = 0; m <= n; m++)
    {
      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(
          &parameterNameBuffer[0],
          "degree%d:sphericalHarmonicG_n%dm%d_epoch%d",
          n,
          n,
          m,
          p_igrf_params_out->epochYear);

      /* Load coefficient into array */
      GParser_loadDouble(
          &GParser_state,
          p_dic,
          &p_igrf_params_out->gEpochCoefficients_nT[n][m],
          &parameterNameBuffer[0]);

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(
          &parameterNameBuffer[0],
          "degree%d:sphericalHarmonicG_n%dm%d_linearRate%d",
          n,
          n,
          m,
          p_igrf_params_out->epochYear);

      /* Load coefficient into array */
      GParser_loadDouble(
          &GParser_state,
          p_dic,
          &p_igrf_params_out->gLinearRateCoefficients_nTs[n][m],
          &parameterNameBuffer[0]);

      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(
          &parameterNameBuffer[0],
          "degree%d:sphericalHarmonicH_n%dm%d_epoch%d",
          n,
          n,
          m,
          p_igrf_params_out->epochYear);

      /* Load coefficient into array */
      GParser_loadDouble(
          &GParser_state,
          p_dic,
          &p_igrf_params_out->hEpochCoefficients_nT[n][m],
          &parameterNameBuffer[0]);
      /* Clear the parameter name buffer */
      GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

      /* Write the name of the parameter to load into buffer */
      sprintf(
          &parameterNameBuffer[0],
          "degree%d:sphericalHarmonicH_n%dm%d_linearRate%d",
          n,
          n,
          m,
          p_igrf_params_out->epochYear);

      /* Load coefficient into array */
      GParser_loadDouble(
          &GParser_state,
          p_dic,
          &p_igrf_params_out->hLinearRateCoefficients_nTs[n][m],
          &parameterNameBuffer[0]);
    }
  }

  /* Close parameters */
  GParser_closeParams(&GParser_state, p_dic);

  return GCONST_TRUE;
}
