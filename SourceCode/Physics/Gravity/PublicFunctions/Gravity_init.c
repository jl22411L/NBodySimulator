/*
 *    @File:         Gravity_init.c
 *
 *    @ Brief:       Initialises the gravity module and loads params into param
 *                   struct.
 *
 *    @ Date:        29/04/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"

/* Data include */
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GParser/GParser.h"
#include "GZero/GZero.h"

int Gravity_init(
    Gravity_Params *p_gravityParams_in,
    const char     *p_paramsFilePath)
{
  /* Defining local variables */
  dictionary   *p_dic;
  GParser_State GParser_state;

  /* Clearing  variables */
  GZero(&GParser_state, GParser_State);
  GZero(p_gravityParams_in, Gravity_Params);
  p_dic = NULL;

  /* Loading parameters into dictionaries */
  p_dic = GParser_loadParams(&GParser_state, p_paramsFilePath);

  /* Check parameters are laoded */
  if (p_dic == NULL)
  {
    GError("Params weren't loaded correctly");
  }

  /* Clear the struct to load */
  GZero(p_gravityParams_in, Gravity_Params);

  /* ------------- Load parameters into Gravity Params struct -------------- */

  GParser_loadUInt8(
      &GParser_state,
      p_dic,
      &(p_gravityParams_in->gravityModel),
      "GravityParameters:GravityModel");

  GParser_loadDouble(
      &GParser_state,
      p_dic,
      &(p_gravityParams_in->seaLevelGravitationalAcceleration_ms2),
      "GravityParameters:SeaLevelGravitationalAcceleration");

  /* -------------------------- Parameter Checks --------------------------- */

  /*
   * Check that gravity acceleration is not 0 for FlatEarthgravityModel. Advise
   * otherwise if is so.
   */
  if ((p_gravityParams_in->gravityModel == FlatEarthGravityModel) &&
      (p_gravityParams_in->seaLevelGravitationalAcceleration_ms2 == 0))
  {
    GWarn("Flat Earth model selected but gravity acceleration is set to 0.");
    GWarn(
        "In future use NoGravityModel (%d) for this type of case",
        FlatEarthGravityModel);
  }

  /*
   * Check that gravitational acceleration is 0 if the model is not
   * FlatEarthGravityModel
   */
  else if (

      (p_gravityParams_in->gravityModel != FlatEarthGravityModel) &&
      (p_gravityParams_in->seaLevelGravitationalAcceleration_ms2 != 0))
  {
    GWarn(
        "Gravity model 'FlatEarthGravityModel' (%d) is not being used,"
        "however, gravitational acceleartion is set to %lf",
        FlatEarthGravityModel,
        p_gravityParams_in->seaLevelGravitationalAcceleration_ms2);
    GWarn("It is advised to set gravitational acceleration to 0 if not useing "
          "Flat Earth Model");
  }

  /* Close params */
  GParser_closeParams(&GParser_state, p_dic);

  return GCONST_TRUE;
}
