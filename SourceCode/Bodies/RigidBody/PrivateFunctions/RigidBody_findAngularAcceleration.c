/*
 *    @File:         RigidBody_findAngularAcceleration.c
 *
 *    @ Brief:       Finds the acceleration from a Moment
 *
 *    @ Date:        23/02/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "RigidBody/DataStructs/RigidBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int RigidBody_findAngularAcceleration(RigidBody_State *p_rigidBody_state_in)
{
  /* Declaring local variables */
  double invInertiaMatrix[3][3];
  double angularMomentum_radkgm2_Bod[3];
  double crossRotationalMoments_Nm_Bod[3];
  double effectiveNetMoment_Nm_Bod[3];

  /* Clearing local variables */
  GZero(&invInertiaMatrix[0][0], double[3][3]);
  GZero(&angularMomentum_radkgm2_Bod[0], double[3]);
  GZero(&crossRotationalMoments_Nm_Bod[0], double[3]);
  GZero(&effectiveNetMoment_Nm_Bod, double[3]);

  /* Find the inverse of the inertia matrix */
  GMath_invMat(&p_rigidBody_state_in->inertiaMatrix_Bod_kgm2[0][0],
               &invInertiaMatrix[0][0],
               3);

  /* Find the angular momentum of the rigid body */
  GMath_matMul(&invInertiaMatrix[0][0],
               3,
               3,
               &p_rigidBody_state_in->angularVelocity_rads_Bod[0],
               3,
               1,
               &angularMomentum_radkgm2_Bod[0]);

  /* Find the cross rotational inertia moements */
  GMath_crossProduct(&p_rigidBody_state_in->angularVelocity_rads_Bod[0],
                     &angularMomentum_radkgm2_Bod[0],
                     &crossRotationalMoments_Nm_Bod[0]);

  /* Find the effective net moments */
  GMath_matSub(p_rigidBody_state_in->resultantMoment_Nm_Bod,
               3,
               1,
               &crossRotationalMoments_Nm_Bod[0],
               3,
               1,
               &effectiveNetMoment_Nm_Bod[0]);

  /* Find the angular acceleration of the body */
  GMath_matMul(&invInertiaMatrix[0][0],
               3,
               3,
               &effectiveNetMoment_Nm_Bod[0],
               3,
               1,
               &p_rigidBody_state_in->angularAcceleration_rads2_Bod[0]);

  return GCONST_TRUE;
}
