/*
 *    @File:         SunSensor_checkForBlocking.c
 *
 *    @Brief:        Function which is used to see if celestial body is blocking
 *                   sensor from detecting sun.
 *
 *    @Date:         13/11/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
#include "CelestialBody/DataStructs/CelestialBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int SunSensor_checkForBlocking(double               *p_sunPosition_Fix_m_in,
                               double               *p_bodyPosition_Fix_m_in,
                               CelestialBody_State **p_celestialBodyList_in,
                               int                   nCelestialBodies_in)
{
  /* Declare local variables */
  double a;
  double b;
  double c;
  double x1;
  double y1;
  double z1;
  double x2;
  double y2;
  double z2;
  double x3;
  double y3;
  double z3;
  int    i;

  /* Extract coefficients of satellite */
  x1 = *(p_bodyPosition_Fix_m_in + 0);
  y1 = *(p_bodyPosition_Fix_m_in + 1);
  z1 = *(p_bodyPosition_Fix_m_in + 2);
  x2 = *(p_sunPosition_Fix_m_in + 0);
  y2 = *(p_sunPosition_Fix_m_in + 1);
  z2 = *(p_sunPosition_Fix_m_in + 2);

  /*!
   * Method involves finding the coefficients of a quadratic equation:
   *    a*u^2 + b*u + c = 0
   *
   * Taking the quadratic root formula:
   *  u = (-b +/- sqrt(b^2 - 4*a*c)) / (2 * a)
   *
   * It can be seen that if:
   *  b^2 - 4*a*c > 0 -> sphere is intersecting line
   *  b^2 - 4*a*c = 0 -> line is tangent to sphere
   *  b^2 - 4*a*c < 0 -> line is not intersecting sphere
   *
   * [Ref: https://paulbourke.net/geometry/circlesphere/index.html#linesphere]
   */

  /* Find a coefficient */
  a = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1) + (z2 - z1) * (z2 - z1);

  for (i = 0; i < nCelestialBodies_in; i++)
  {
    /* Extract coefficients of celestial */
    x3 = (*(p_celestialBodyList_in + i))->rigidBody_state.position_m_Fix[0];
    y3 = (*(p_celestialBodyList_in + i))->rigidBody_state.position_m_Fix[1];
    z3 = (*(p_celestialBodyList_in + i))->rigidBody_state.position_m_Fix[2];

    /* Find b coefficient */
    b = 2 *
        ((x2 - x1) * (x1 - x3) + (y2 - y1) * (y1 - y3) + (z2 - z1) * (z1 - z3));

    /* Find c coeffieint */
    c = x3 * x3 + y3 * y3 + z3 * z3 + x1 * x1 + y1 * y1 + z1 * z1 -
        2 * (x3 * x1 + y3 * y1 + z3 * z1) -
        ((*(p_celestialBodyList_in + i))->equitorialRadius_m) *
            ((*(p_celestialBodyList_in + i))->equitorialRadius_m);

    if ((b * b - 4 * a * c) < 0)
    {
      return GCONST_FALSE;
    }
  }

  return GCONST_TRUE;
}