/*
 *    @File:         RigidBody_PublicFunctions.h
 *
 *    @ Brief:       Header file that contains the public functions for the
 * RigidBody module
 *
 *    @ Date:        24/01/2024
 *
 */

#ifndef H_RIGIDBODY_PUBLICFUNCTIONS_H
#define H_RIGIDBODY_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GParser/GParser.h"


/*!
 * @details     Function which loads the parameters into the Rigid Body
 *
 * @param[in]   p_RigidBody_state
 *              Pointer to a rigid body state struct, which will be loaded with
 * the initial conditions of the simulation.
 */
int RigidBody_init(RigidBody_State *p_Rigidbody_state);

#ifdef __cplusplus
}
#endif

#endif /* H_RIGIDBODY_PUBLICFUNCTIONS_H */