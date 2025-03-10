/*!
 *    @File:         KeplarianPropogation_findPositionInInertCen.c
 *
 *    @Brief:        Private function which will convert the orbital position
 *                   from the perificol frame to the inertical centre frame.
 *
 *    @Date:         09/03/2025
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

int KeplarianPropogation_findPositionInInertCen(
    double *p_orbitalPosition_Per_in,
    double  inclintaion_rad_in,
    double  argOfPeriapsis_rad_in,
    double  raans_rad_in,
    double *p_orbitalPosition_InertCen_out)
{
  /* Declare local variables */
  double rotationDcm[3][3];
  double rotationEul123[3];
  double vectorBuffer1[3];
  double vectorBuffer2[3];

  /* Clear variables */
  GZero(&(rotationDcm[0][0]), double[3][3]);
  GZero(&(vectorBuffer1[0]), double[3]);
  GZero(&(vectorBuffer2[0]), double[3]);

  /* Create euler angle vector for argument of periapsis */
  rotationEul123[0] = 0.0;
  rotationEul123[1] = 0.0;
  rotationEul123[2] = -argOfPeriapsis_rad_in;

  /* Find rotation DCM for argument of periapsis */
  GMath_eul2Dcm(&(rotationEul123[0]), &(rotationDcm[0][0]));

  /* Rotate the orbital position */
  GMath_matMul(&(rotationDcm[0][0]),
               3,
               3,
               p_orbitalPosition_Per_in,
               3,
               1,
               &(vectorBuffer1[0]));

  /* Create euler angle vector for inclination */
  rotationEul123[0] = -inclintaion_rad_in;
  rotationEul123[1] = 0.0;
  rotationEul123[2] = 0.0;

  /* Find rotation DCM for argument of periapsis */
  GMath_eul2Dcm(&(rotationEul123[0]), &(rotationDcm[0][0]));

  /* Rotate the orbital position */
  GMath_matMul(&(rotationDcm[0][0]),
               3,
               3,
               &(vectorBuffer1[0]),
               3,
               1,
               &(vectorBuffer2[0]));

  /* Create euler angle vector for RAANS */
  rotationEul123[0] = 0.0;
  rotationEul123[1] = 0.0;
  rotationEul123[2] = -raans_rad_in;

  /* Find rotation DCM for argument of RAANS */
  GMath_eul2Dcm(&(rotationEul123[0]), &(rotationDcm[0][0]));

  /* Rotate the orbital position to Inertial Centric Frame */
  GMath_matMul(&(rotationDcm[0][0]),
               3,
               3,
               &(vectorBuffer2[0]),
               3,
               1,
               p_orbitalPosition_InertCen_out);

  return GCONST_TRUE;
}