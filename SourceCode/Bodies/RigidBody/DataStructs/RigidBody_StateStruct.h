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
#include "GConst/GConst.h"

/*!
 * @brief      Structure containint the params for the rigid body
 */
typedef struct RigidBody_StateStruct
{
  /*--------------------------------------------------------------------------*
   *                            INERTIA PROPERTIES                            *
   *--------------------------------------------------------------------------*/

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

  /*--------------------------------------------------------------------------*
   *                          TRANSLATIONAL VECTORS                           *
   *--------------------------------------------------------------------------*/

  /*!
   * @brief   Resultant gravity force vector present on the satellite
   *
   * @unit    Newtons
   * @frame   Fixed Frame
   */
  double gravityForce_N_Fixed[3];

  /*!
   * @brief   Vector containing the resultant force of the satellite.
   *
   * @unit    Newtons
   * @frame   Fixed Frame
   */
  double resultantForce_N_Fixed[3];

  /*!
   * @details   Body acceleration vector of rigid body
   *
   * @unit      ms^-2
   * @frame     Rigid Body fixed frame
   */
  double acceleration_ms2_Fix[3];

  /*!
   * @details   Body velocity vector of rigid body
   *
   * @unit      ms^-1
   * @frame     Rigid Body fixed frame
   */
  double velocity_ms_Fix[3];

  /*!
   * @details   Position of body frame in the fixed frame
   *
   * @unit      m
   * @frame     fixed frame -> body frame
   */
  double position_m_Fix[3];

  /*--------------------------------------------------------------------------*
   *                              ANGULAR VECTORS                             *
   *--------------------------------------------------------------------------*/

  /*!
   * @brief   Vector containing the resultant Moment of the satellite.
   *
   * @unit    NewtonMeters
   * @frame   Body Frame
   */
  double resultantMoment_Nm_Bod[3];

  /*!
   * @details   Angular acceleration of the rigid body in the body frame
   *
   * @unit      rad/s
   * @frame     Body Frame
   */
  double angularAcceleration_rads2_Bod[3];

  /*!
   * @details   Angular velocity of the rigid body in the body frame
   *
   * @unit      rad/s
   * @frame     Body Frame
   */
  double angularVelocity_rads_Bod[3];

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
  double quaternionRate_FixedToBody[4];

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
  double quaternion_FixedToBody[4];

  /*--------------------------------------------------------------------------*
   *                             BODY INFORMATION                             *
   *--------------------------------------------------------------------------*/

  /*!
   * @details   Body Name
   *
   * @unit      N/A
   * @frame     N/A
   */
  char bodyName[GCONST_BUFFER_256];

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
