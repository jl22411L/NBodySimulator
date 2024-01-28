/*
 *    @File:         main.c
 *
 *    @ Brief:       Rigid Body Unit Test
 *
 *    @ Description: This script is a unit test for the Rigid Body structure
 *
 *    @ Date:        24/01/2024
 *
 */

#include "RigidBody/PublicFunctions/RigidBody_PublicFunctions.h"
#include "RigidBody/RigidBody.h"

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GUtilities/GUtilities.h"

int main()
{
  /* Declaring local variables */
  RigidBody_State RigidBody_state;

  GUtilities_init("parameters/SimulationParameters.ini");

  RigidBody_init(&RigidBody_state);

  return GCONST_EXIT_SUCCESS;
}