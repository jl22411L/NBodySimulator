/*!
 *    @File:         Igrf_convertFromNedToGeoCen.c
 *
 *    @Brief:        Function which converts magnetic field from NED to
 *                   GeoCentric frame.
 *
 *    @Date:         01/02/2025
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

int Igrf_convertFromNedToGeoCen(double *p_magneticField_Ned_nT_in,
                                double *p_sphericalCoordinates_in,
                                double *p_magneticField_GeoCen_nT_out)
{
  /* Declare local variables */
  double frameRotationQuat_GeoCenToNed[4];
  double euler_GeoCenToNed[3];

  /* Clear Variables */
  GZero(&(frameRotationQuat_GeoCenToNed[0]), double[4]);
  GZero(&(euler_GeoCenToNed[0]), double[3]);

  /* Set Euler Angle Vector */
  euler_GeoCenToNed[0] = 0;
  euler_GeoCenToNed[1] =
      90 * GCONST_DEG_TO_RAD + *(p_sphericalCoordinates_in + 2);
  euler_GeoCenToNed[2] = *(p_sphericalCoordinates_in + 1);

  /* Find quaternion of rotation from NED TO GeoCen */
  GMath_eul2Quat(&(euler_GeoCenToNed[0]), &(frameRotationQuat_GeoCenToNed[0]));

  /*!
   * The quaternion is a rotation of a point from the GeoCen frame to the Ned
   * frame. To rotate a point from the Ned frame to the GeoCen frame, you
   * need rotate the GeoCen frame to the Ned frame. (Inverse rotation of point
   * essentially)
   */
  GMath_quaternionFrameRotation(p_magneticField_GeoCen_nT_out,
                                p_magneticField_Ned_nT_in,
                                &(frameRotationQuat_GeoCenToNed[0]));

  return GCONST_TRUE;
}