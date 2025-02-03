/*
 *    @File:         Igrf_findPositionInGeocentricBodyFrame.c
 *
 *    @Brief:        Function which finds the position of the orbiting body in
 *                   the geocentric frame.
 *
 *    @Date:         22/10/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int Igrf_findPositionInGeocentricBodyFrame(
    double *p_secondryBodyPosition_fix_in,
    double *p_primaryBodyPosition_fix_in,
    double *p_primaryBodyQuat_fixToBod_in,
    double *p_secondryBodyCartesianPosition_GeoCen_out)
{
  /* Declare local variables */
  double intermediateVector[3];

  /* Clear Variables */
  GZero(&(intermediateVector[0]), double[3]);

  /* Find the position of the orbiting body relative to the geocentric body */
  GMath_vectorSub(p_secondryBodyPosition_fix_in,
                  p_primaryBodyPosition_fix_in,
                  &intermediateVector[0]);

  /* Rotate the frame to make the vector in the geocentric frame of the body */
  GMath_quaternionFrameRotation(p_secondryBodyCartesianPosition_GeoCen_out,
                                &intermediateVector[0],
                                p_primaryBodyQuat_fixToBod_in);

  return GCONST_TRUE;
}
