/*!
 *    @File:         CelestialBody_checkRotationAngle.c
 *
 *    @Brief:        Function which will check the rotation angle of the
 *                   celestial body and determine if that is in line with the
 *                   simulated time of the simulation.
 *
 *    @Date:         05/02/2025
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "CelestialBody/ConstantDefs/CelestialBody_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GMath/GMath.h"
#include "GZero/GZero.h"

int CelestialBody_checkRotationAngle(double *p_quaternion_InertCenToGeoCen_in,
                                     double  celestialBodySideRealTime_s_in,
                                     double  simTime_s_in)
{
  /* Declare local variables */
  double  unitQuaternion_InertCenToGeoCen[4];
  double  simulatedRotatedAngle_rad;
  double  theoreticalRotatedAngle_rad;
  double  angularSpeed_rads;
  double  error_rad;
  uint8_t i;

  /* Clear variables */
  GZero(&(unitQuaternion_InertCenToGeoCen[0]), double[4]);

  /* Set numbers below toelrance to zero */
  for (i = 0; i < 4; i++)
  {
    if ((*(p_quaternion_InertCenToGeoCen_in + i)) *
            (*(p_quaternion_InertCenToGeoCen_in + i)) >
        CELESTIALBODY_ROTATION_ANGLE_TOLERANCE_RAD *
            CELESTIALBODY_ROTATION_ANGLE_TOLERANCE_RAD)
    {
      unitQuaternion_InertCenToGeoCen[i] =
          *(p_quaternion_InertCenToGeoCen_in + i);
    }
  }

  /* Find unit quaternion */
  GMath_findUnitQuaternion(&(unitQuaternion_InertCenToGeoCen[0]),
                           &(unitQuaternion_InertCenToGeoCen[0]));

  /* Find simulated rotated angle from the quaternion in range 0-2*PI*/
  simulatedRotatedAngle_rad =
      2 * GCONST_PI - 2 * acos(unitQuaternion_InertCenToGeoCen[3]);

  /* Find the angular speed of the body */
  angularSpeed_rads = 2 * GCONST_PI / celestialBodySideRealTime_s_in;

  /* Find the theoritcal rotated angle of the body being simulated */
  theoreticalRotatedAngle_rad =
      angularSpeed_rads * (simTime_s_in - GCONST_J2000_UNIX_TIME_S);

  /* Floor the theoretical angle so that it is found within range 0-2*PI */
  theoreticalRotatedAngle_rad =
      fmod(theoreticalRotatedAngle_rad, 2 * GCONST_PI);

  /* Find the absolute value of the error */
  GMath_abs(theoreticalRotatedAngle_rad - simulatedRotatedAngle_rad,
            &error_rad);

  printf("%lf, %lf, %lf, %lf\n",
         simTime_s_in,
         error_rad,
         theoreticalRotatedAngle_rad,
         simulatedRotatedAngle_rad);

  /* Compare results to make sure they are within tolerance */
  if (error_rad > CELESTIALBODY_ROTATION_ANGLE_TOLERANCE_RAD)
  {
    GError("Simulated angle is outside tolerance of theoretical angle.\n"
           "simulatedRotatedAngle_rad = %lf\n"
           "theoreticalRotatedAngle_rad = %lf\n",
           simulatedRotatedAngle_rad,
           theoreticalRotatedAngle_rad);
  }

  return GCONST_TRUE;
}