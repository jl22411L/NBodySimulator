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
 * @brief       Function which loads the parameters into the Rigid Body
 *
 * @param[in]   p_rigidBody_state_in
 *              Pointer to a rigid body state struct, which will be loaded
 * with the initial conditions of the simulation.
 *
 * @param[in]   p_paramFilename_in
 *              String containing the name of the ini file containing the
 *              parameters for the rigid body.
 *
 * @param[in]   p_bodyName_in
 *              String containing the name of the body.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int RigidBody_init(
    RigidBody_State *p_rigidBody_state_in,
    const char      *p_paramFilename_in);

/*!
 * @brief       Will archive the members of the rigid body before integrating
 *              all the members.
 *
 * @param[in]   p_rigidBody_state_in
 *              Pointer to the rigid body state struct.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int RigidBody_step(RigidBody_State *p_rigidBody_state_in);

/*!
 * @brief       Closes the archive of the rigid body.
 *
 * @param[in]   p_rigidBody_state_in
 *              Pointer with the address of the rigid body struct.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int RigidBody_terminate(RigidBody_State *p_rigidBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_RIGIDBODY_PUBLICFUNCTIONS_H */
