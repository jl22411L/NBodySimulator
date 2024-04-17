/*
 *    @File:         Gravity_PublicFUnctions.h
 *
 *    @ Brief:       Contains the public functions for Gravity Module
 *
 *    @ Date:        17/04/2024
 *
 */

#ifndef H_GRAVITY_PUBLICFUNCTIONS_H
#define H_GRAVITY_PUBLICFUNCTIONS_H

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

/*!
 * @brief       Will find the total vectors between all rigid bodies. Takes in
 *              a pointer to an array of rigid body structs. Will find the
 *              distance between each rigid body in the fixed frame. From this
 *              it will then find the gravity between two bodies and sum this
 *              to the total gravity force for said body. It will repeat the
 *              process for all the other bodies.
 *
 * @param[in]   p_rigidBodyArray_in
 *              Pointer to first rigid body in an array of rigid bodies
 *
 * @param[in]   nRigidBoies_in
 *              Integer containing the number of rigid bodies to compute the
 *              total gravity force.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Gravity_findGravity(
    RigidBody_State *p_rigidBodyArray_in,
    int              nRigidBoies_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GRAVITY_PUBLICFUNCTIONS_H */
