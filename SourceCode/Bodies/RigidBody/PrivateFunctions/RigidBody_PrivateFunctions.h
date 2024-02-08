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
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

extern int RigidBody_createArchives(RigidBody_State *p_rigidBody_state_in);

#ifdef __cplusplus
}
#endif

#endif /* H_RIGIDBODY_PRIVATEFUNCTIONS_H */