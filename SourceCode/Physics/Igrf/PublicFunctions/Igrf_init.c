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
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Igrf_init(Igrf_Params *p_igrfParams_in, const char *p_paramsFilePath)
{
  /* Declare local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;
  char          parameterNameBuffer[IGRF_MAX_STRING_BUFFER_SIZE];
  uint8_t       i;

  /* Clear the Igrf Params Struct */
  GZero(&GParser_state, GParser_State);
  GZero(p_igrfParams_in, Igrf_Params);
  p_dic = NULL;

  /* Loading parameters into dictionaries */
  p_dic = GParser_loadParams(&GParser_state, p_paramsFilePath);

  /* Check parameters are laoded */
  if (p_dic == NULL)
  {
    GError("Params weren't loaded correctly");
  }

  /* ------------------------------------------------------------------------ *
   * LOAD PARAMETERS INTO STRUCT
   * ------------------------------------------------------------------------ */

  for (i = 0; i <= p_igrfParams_in->nDegree; i++)
  {
    /* Clear name buffer */
    GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

    /* Write to name buffer */
    sprintf(
        &parameterNameBuffer[0],
        "degree%d:sphericalHarmonicG_n%dm%d_epoch%d",
        p_igrfParams_in->nDegree,
        p_igrfParams_in->nDegree,
        i,
        p_igrfParams_in->epochYear);

    /* Load first linear rate gCoefficient */
    GParser_loadDouble(
        &GParser_state,
        p_dic,
        &p_igrfParams_in->gCoefficients[i],
        &parameterNameBuffer[0]);

    /* Clear name buffer */
    GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

    /* Write to name buffer */
    sprintf(
        &parameterNameBuffer[0],
        "degree%d:sphericalHarmonicG_n%dm%d_linearRate%d",
        p_igrfParams_in->nDegree,
        p_igrfParams_in->nDegree,
        i,
        p_igrfParams_in->epochYear);

    /* Load first linear rate gCoefficient */
    GParser_loadDouble(
        &GParser_state,
        p_dic,
        &p_igrfParams_in->gLinearRateCoefficients[i],
        &parameterNameBuffer[0]);

    /* Clear name buffer */
    GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

    /* Write to name buffer */
    sprintf(
        &parameterNameBuffer[0],
        "degree%d:sphericalHarmonicH_n%dm%d_epoch%d",
        p_igrfParams_in->nDegree,
        p_igrfParams_in->nDegree,
        i,
        p_igrfParams_in->epochYear);

    /* Load first linear rate hCoefficient */
    GParser_loadDouble(
        &GParser_state,
        p_dic,
        &p_igrfParams_in->hCoefficients[i],
        &parameterNameBuffer[0]);

    /* Clear name buffer */
    GZero(&parameterNameBuffer[0], char[IGRF_MAX_STRING_BUFFER_SIZE]);

    /* Write to name buffer */
    sprintf(
        &parameterNameBuffer[0],
        "degree%d:sphericalHarmonicH_n%dm%d_linearRate%d",
        p_igrfParams_in->nDegree,
        p_igrfParams_in->nDegree,
        i,
        p_igrfParams_in->epochYear);

    /* Load first linear rate gCoefficient */
    GParser_loadDouble(
        &GParser_state,
        p_dic,
        &p_igrfParams_in->hLinearRateCoefficients[i],
        &parameterNameBuffer[0]);
  }

  return GCONST_TRUE;
}
