/*
 *    @File:         Gravity_PrivateFucntions
 *
 *    @ Brief:       Header file containing the private functions for the
 *                   gravity module.
 *
 *    @ Date:        17/04/2024
 *
 */

#ifndef H_GRAVITY_PRIVATEFUNCTIONS_H
#define H_GRAVITY_PRIVATEFUNCTIONS_H

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
 * @brief       Finds the gravity force between two bodies.
 *
 * @param[in]   p_internalRigidBody_in
 *              Pointer to internal body which the calcualted gravity force
 *              between the two bodies will be applied. (The gravity force is
 *              being applied to this body)
 *
 * @param[in]   p_externalRigidBody_in
 *              Pointer to external body which the calculated gravity force
 *              is based on. (The grvaity force is an effect caused by this
 *              body)
 *
 * @param[in]   p_individualGravityVector_N_fixed_out
 *              Pointer to double vector which the gravity force will be
 *              added to. This way, this function accumilates the results
 *              of the rgavity force between all the external bodies to
 *              this vector.
 *
 *              WARNING: It is very important that the clearing of this
 *                       vector is handeled appropriately.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Gravity_findGravityForceBetweenBodies(
    RigidBody_State *p_internalRigidBody_in,
    RigidBody_State *p_externalRigidBody_in,
    double          *p_individualGravityVector_N_fixed_out);

#ifdef __cplusplus
}
#endif

#endif /* H_GRAVITY_PRIVATEFUNCTIONS_H */
