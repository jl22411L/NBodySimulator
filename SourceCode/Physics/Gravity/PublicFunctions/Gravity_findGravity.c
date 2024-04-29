/*
 *    @File:         Gravity_findSatelliteGravity.c
 *
 *    @ Brief:       Finds gravity force on satellites
 *
 *    @ Date:        20/03/2024
 *
 */

#include <math.h>

/* Function Includes */
#include "Gravity/PrivateFunctions/Gravity_PrivateFunctions.h"

/* Structure Include */
#include "Gravity/DataStructs/Gravity_StateStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Gravity_findGravity(
    Gravity_ParamsStruct *p_gravityParams_in,
    RigidBody_State      *p_rigidBodyArray_in,
    int                   nRigidBodies_in)
{
  /* Determine what model is being used for gravity */
  switch (p_gravityParams_in->gravityModel)
  {
  case (NoGravityModel):
    /* Apply the no gravity model to the array of rigid bodies */
    Gravity_noGravityModel(p_rigidBodyArray_in, nRigidBodies_in);
    break;

  case (FlatEarthGravityModel):
    /* Apply the flat earth gravity model on array of rigid bodies */
    Gravity_flatEarthGravityModel(
        p_gravityParams_in,
        p_rigidBodyArray_in,
        nRigidBodies_in);
    break;

  case (DualBodyGravityModel):
    // TODO
    break;

  case (NBodyGravityModel):
    // TODO
    break;

  default:
    GError(
        "Gravity Model '%d' is not recognised as a valid gravity model",
        p_gravityParams_in->gravityModel);
    break;
  }

  return GCONST_TRUE;
}
// {
//   /* Defining Local Variables */
//   int i;
//   int j;
//   int k;

//   /* Iterate through each body and find resultant gravity force */
//   for (i = 0; i < nRigidBoies_in; i++)
//   {
//     /* Clear gravity vector for internal body */
//     GZero((p_rigidBodyArray_in + i), double[3]);

//     /* Find a gravity force for the internal body by iterating through
//     all
//      * the external bodies and acumilating the gravity forces caused by
//      them.
//      */
//     for (j = 0; j < nRigidBoies_in; j++)
//     {
//       /* For all bodies except the current one, find the effect of
//       gravity */ if (j != i)
//       {
//         Gravity_findGravityForceBetweenBodies(
//             (p_rigidBodyArray_in + i),
//             (p_rigidBodyArray_in + j),
//             &p_rigidBodyArray_in->gravityForce_N_Fixed[0]);
//       }
//     }
//   }

//   return GCONST_TRUE;
// }
