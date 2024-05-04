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
#include "Gravity/DataStructs/Gravity_ParamsStruct.h"
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Finds the gravity force between two bodies. Uses newtonian law
 *              to calcualte the gravity force caused on the bodies. Assumes
 *              that the size of the rigid body array is 2.
 *
 *              Finds the distance of body 2 relative to body 1. From this,
 *              the gravity scalar is found. This is then used to find the
 *              gravity forec on body 1 and body 2. Body 2 has the same
 *              magnitude but in the opposite direction.
 *
 * @param[in]   p_rigidBodyArray_in
 *              Pointer to an array of rigid bodies. It is assumed that the size
 *              is equal to 2.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Gravity_dualBodyGravityModel(RigidBody_State **p_rigidBodyArray_in);

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
 * @param[in]   p_internalBodyGravityVector_N_fixed_out
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
    double          *p_internalBodyGravityVector_N_fixed_out);

/*!
 * @brief       Model which uses the gravitational acceleration parameter and
 *              bodies mass to find the gravity force on the body. It then sets
 *              the Z component of the fixed body frame to the negative of this
 *              value, to simulate the body having a force pulling it to the
 *              ground.
 *
 * @param[in]   p_gravityPrams_in
 *              Pointer to gravity params struct.
 *
 * @param[in]   p_rigidBodyArray_in
 *              Pointer to array of rigid bodies
 *
 * @param[in]   nRigidBodies_in
 *              Integer containing the number of rigid bodies in array.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Gravity_flatEarthGravityModel(
    Gravity_Params   *p_gravityPrams_in,
    RigidBody_State **p_rigidBodyArray_in,
    int               nRigidBodies_in);

/*!
 * @brief       Sets the gravity force in the fixed frame to 0, for an array
 *              of rigid body structs.
 *
 * @param[in]   p_rigidBody_array_in
 *              Pointer to an array of rigidBody structs which will have the
 *              gravity force set to 0.
 *
 * @param[in]   nRigidBodies_in
 *              Number of bodies in the rigid body struct
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
extern int Gravity_noGravityModel(
    RigidBody_State **p_rigidBody_array_in,
    int               nRigidBodies_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GRAVITY_PRIVATEFUNCTIONS_H */
