/*!
 *    @File:         KeplarianPropogation_keplarianToCartesian.c
 *
 *    @Brief:        Function which will find the position of a body in
 *                   cartesian form from the keplarian elements.
 *
 *    @Date:         09/03/2025
 *
 */

#include <math.h>

/* Function Includes */
#include "Guidance/KeplarianPropogation/PrivateFunctions/KeplarianPropogation_PrivateFunctions.h"

/* Structure Include */
/* None */

/* Data include */
#include "Gravity/ConstantDefs/Gravity_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int KeplarianPropogation_keplarianToCartesian(
    double  massBody1_kg_in,
    double  massBody2_kg_in,
    double  semiMajorAxis_m_in,
    double  eccentricity_in,
    double  inclintaion_rad_in,
    double  argOfPeriapsis_rad_in,
    double  raans_rad_in,
    double  timeSincePeriapsis_s_in,
    double  simTime_s_in,
    double *p_orbitalPosition_InertCen_m_out)
{
  /* Declare local variables */
  double gravitationalParameter_m3kg2s2;
  double orbitalAngularMomentum_m2s;
  double orbitalTimePeriod_s;
  double averageAngularRate_rads;
  double meanAnomoly_rad;
  double eccentricAnomoly_rad;
  double trueAnomoly_rad;
  double orbitalPositionMag_m;
  double orbitalPosition_Per_m[3];
  double orbitalPosition_InertCen_m[3];
  double changeInTime_s;

  /* Clar Variables */
  GZero(&(orbitalPosition_Per_m[0]), double[3]);
  GZero(&(orbitalPosition_InertCen_m[0]), double[3]);

  /* Find standard gravitational parameter (mu) */
  gravitationalParameter_m3kg2s2 = GRAVITY_UNIVERSAL_GRAVITATIONAL_CONSTANT *
                                   (massBody1_kg_in + massBody2_kg_in);

  /* Find the period of the orbit */
  orbitalTimePeriod_s =
      (2 * GCONST_PI *
       sqrt(pow(semiMajorAxis_m_in, 3) / gravitationalParameter_m3kg2s2));

  /* Find the time since periapsis */
  changeInTime_s =
      fmod(simTime_s_in - timeSincePeriapsis_s_in, orbitalTimePeriod_s);

  /* If the change in time is negative, add a time period to make positive */
  if (changeInTime_s < 0.0)
  {
    changeInTime_s += orbitalTimePeriod_s;
  }

  /* Find average angular rate of orbiting body (body 2) */
  averageAngularRate_rads = 2 * GCONST_PI / orbitalTimePeriod_s;

  /* Find the mean anomoly */
  meanAnomoly_rad = averageAngularRate_rads * changeInTime_s;

  /* Find the Eccentric Anomoly */
  KeplarianPropogation_findEccentricAnomoly(meanAnomoly_rad,
                                            eccentricity_in,
                                            &(eccentricAnomoly_rad));

  /* Find the True Anomoly */
  trueAnomoly_rad =
      2 * atan2(sqrt(1 + eccentricity_in) * tan(eccentricAnomoly_rad / 2),
                sqrt(1 - eccentricity_in));

  /* Find the magnitude of the position of body 2 with respect to body 1 */
  orbitalPositionMag_m =
      semiMajorAxis_m_in * (1 - eccentricity_in * cos(eccentricAnomoly_rad));

  /* Find position of body 2 with respect to body 1 in the Perifocal Frame   */
  orbitalPosition_Per_m[0] = orbitalPositionMag_m * cos(trueAnomoly_rad);
  orbitalPosition_Per_m[1] = orbitalPositionMag_m * sin(trueAnomoly_rad);
  orbitalPosition_Per_m[2] = 0.0;

  /* Find the position of body 2 with respect to body 1 */
  KeplarianPropogation_findPositionInInertCen(&(orbitalPosition_Per_m[0]),
                                              inclintaion_rad_in,
                                              argOfPeriapsis_rad_in,
                                              raans_rad_in,
                                              p_orbitalPosition_InertCen_m_out);

  return GCONST_TRUE;
}