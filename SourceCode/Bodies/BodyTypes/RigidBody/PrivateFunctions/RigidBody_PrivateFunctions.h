/*
 *    @File:         GRigidBody_PrivateFunctions.h
 *
 *    @ Brief:       Private functions for RigidBody module
 *
 *    @ Date:        07/02/2024
 *
 */

#ifndef H_RIGIDBODY_PRIVATEFUNCTIONS_H
#define H_RIGIDBODY_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "BodyTypes/RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @details     Function which will create the archive for the Rigid body. Wukk
 *              call the GArch library and add the necessary columns to the
 *              config file along with creating a csv file to contain the data.
 *
 * @param[in]   p_rigidBody_state_in
 *              Pointer to a rigid body state struct.
 *
 * @param[in]   p_bodyName_in
 *              String with the name of the body.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int RigidBody_createArchives(
    RigidBody_State *p_rigidBody_state_in,
    const char      *p_bodyName_in);

#ifdef __cplusplus
}
#endif

#endif /* H_RIGIDBODY_PRIVATEFUNCTIONS_H */
