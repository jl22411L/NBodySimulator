/*
 *    @File:         RigidBody_StateStruct.c
 *
 *    @ Brief:       Struct containing the state for a rigid body. Note that
 *                   inertia and mass is included because they can change
 *                   during an operation.
 *
 *    @ Date:        20/01/2024
 *
 */

#ifndef H_RIGIDBODY_PARAMS_STRUCT_H
#define H_RIGIDBODY_PARAMS_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"

/*!
 * @brief      Structure containint the params for the rigid body
 */
typedef struct RigidBody_StateStruct
{
  /*!
   * @details   Mass of the rigid body
   *
   * @unit      Kg
   * @Frame     N/A
   */
  double mass;

  /*!
   * @details   Inertia matrix for the rigid body. The matrix is defined as:
   *
   *                                      I_xx, -I_xy, -I_xz
   *            RigidBodyInertiaMatrix = -I_xy,  I_yy, -I_yz
   *                                     -I_xz, -I_yz,  I_zz
   *
   * @unit      Kgm^2
   * @frame     Body Frame
   */
  double inertiaMatrix[3][3];

  /*!
   * @details   Body acceleration vector of rigid body
   *
   * @unit      ms^-2
   * @frame     Rigid Body body frame
   */
  double bodyFrameAcceleration_ms2[3];

  /*!
   * @details   Body velocity vector of rigid body
   *
   * @unit      ms^-1
   * @frame     Rigid Body body frame
   */
  double bodyFrameVeclocity_ms[3];

  /*!
   * @details   Body acceleration vector of rigid body
   *
   * @unit      ms^-2
   * @frame     Rigid Body fixed frame
   */
  double fixedFrameAcceleration_ms2[3];

  /*!
   * @details   Body velocity vector of rigid body
   *
   * @unit      ms^-1
   * @frame     Rigid Body fixed frame
   */
  double fixedFrameVeclocity_ms[3];

  /*!
   * @details   Position of body frame in the fixed frame
   *
   * @unit      m
   * @frame     fixed frame -> body frame
   */
  double position_m[3];

  /*!
   * @details   Angular acceleration of the rigid body in the body frame
   *
   * @unit      rad/s
   * @frame     body frame
   */
  double angularAcceleration_rads2[3];

  /*!
   * @details   Angular velocity of the rigid body in the body frame
   *
   * @unit      rad/s
   * @frame     body frame
   */
  double angularVelocity_rads[3];

  /*!
   * @details   Quaternion rate which describes the rate at which the body frame
   * is rotating relative to the fixed frame.
   *
   *            dq[0] = qx
   *            dq[1] = qy
   *            dq[2] = qz
   *            dq[3] = qs
   *
   * @unit      N/A
   * @frame     Fixed Frame -> Body Frame
   */
  double quaternionRateFixed2Body[4];

  /*!
   * @details   Quaternion to translate from the fixed frame to the body frame
   *
   *            q[0] = qx
   *            q[1] = qy
   *            q[2] = qz
   *            q[3] = qs
   *
   * @unit      N/A
   * @frame     Fixed Frame -> Body Frame
   */
  double quaternionFixed2Body[4];

  /*!
   * @details   Archive struct for RigidBody.
   *
   * @unit      N/A
   * @frame     N/A
   */
  GArchive rigidBodyArchive;

} RigidBody_State;

#ifdef __cplusplus
}
#endif

#endif /* H_RIGIDBODY_PARAMS_STRUCT_H */