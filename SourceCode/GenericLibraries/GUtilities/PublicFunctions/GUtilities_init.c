/*
 *    @File:         GUtilities_init.c
 *
 *    @ Brief:       Function which loads the parameters into the GUtilities
 *                   struct
 *
 *    @ Date:        28/01/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "GUtilities/DataStructs/Utilities_StateStructs.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int GUtilities_init(const char *p_paramsFilePath)
{
  /* Defining local variables */
  dictionary  **dic;
  GParser_State GParser_state;

  /* Clearing local variables */
  GZero(&GParser_state, GParser_State);
  dic = NULL;

  /* Loading parameters into dictionaries */
  dic = GParser_loadParams(&GParser_state, p_paramsFilePath);

  /* Check parameters are laoded */
  if (dic == NULL)
  {
    GError("Params weren't loaded correctly");
  }

  /* ---------------- Load parameters into Utilities struct ---------------- */

  GParser_loadDouble(
      &GParser_state,
      dic,
      &Utilities.simTimeDuration_s,
      "TimeParameters:simTimeDuration");

  GParser_loadDouble(
      &GParser_state,
      dic,
      &Utilities.simTimeStep_s,
      "TimeParameters:simTimeStep");

  GParser_loadDouble(
      &GParser_state,
      dic,
      &Utilities.simTime_s,
      "TimeParameters:simTimeInitial");

  return GCONST_TRUE;
}