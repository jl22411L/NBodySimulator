/*
 *    @File:         JamSail_findMagneticField.c
 *
 *    @Brief:        Finds magnetic field in inertial frame.
 *
 *    @Date:         27/04/2025
 *
 */

#include <math.h>

/* Function Includes */
#include "Igrf/PrivateFunctions/Igrf_PrivateFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int JamSail_findMagneticField(Igrf_Params    *p_igrfModel_params_in,
                              JamSail_Params *p_jamSail_params_in,
                              double *p_sphericalCoordinates_GeoCen_m_in,
                              double  simTime_s_in,
                              double *p_magneticField_Ned_nT_out)
{
  /* Declare local variables */
  double gCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double hCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double sphericalPosition_GeoCent_m[3];

  /* Clear Buffers */
  GZero(&sphericalPosition_GeoCent_m[0], double[3]);

  /* Find spherical coordiantes with Colatitude */
  sphericalPosition_GeoCent_m[0] = *(p_sphericalCoordinates_GeoCen_m_in + 0);
  sphericalPosition_GeoCent_m[1] = *(p_sphericalCoordinates_GeoCen_m_in + 1);
  sphericalPosition_GeoCent_m[2] =
      GCONST_PI / 2 - *(p_sphericalCoordinates_GeoCen_m_in + 2);

  /* Check tolerances for IGRF */
  Igrf_checkTolerances(&sphericalPosition_GeoCent_m[0]);

  /* Fing the gaussian coefficients for the current sim time */
  Igrf_findCoefficients(&gCoefficients_nT[0][0],
                        &hCoefficients_nT[0][0],
                        simTime_s_in,
                        &p_jamSail_params_in->igrfModel_params);

  /* Adding dipole */
  *(p_magneticField_Ned_nT_out + 0) =
      -(p_jamSail_params_in->earthEqutorialRadius_m /
        sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (gCoefficients_nT[1][0] * sin(sphericalPosition_GeoCent_m[2]) -
       (gCoefficients_nT[1][1] * cos(sphericalPosition_GeoCent_m[1]) +
        hCoefficients_nT[1][1] * sin(sphericalPosition_GeoCent_m[1])) *
           cos(sphericalPosition_GeoCent_m[2]));

  *(p_magneticField_Ned_nT_out + 1) =
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (gCoefficients_nT[1][1] * sin(sphericalPosition_GeoCent_m[1]) -
       hCoefficients_nT[1][1] * cos(sphericalPosition_GeoCent_m[1]));

  *(p_magneticField_Ned_nT_out + 2) =
      -2 *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (p_jamSail_params_in->earthEqutorialRadius_m /
       sphericalPosition_GeoCent_m[0]) *
      (gCoefficients_nT[1][0] * cos(sphericalPosition_GeoCent_m[2]) +
       (gCoefficients_nT[1][1] * cos(sphericalPosition_GeoCent_m[1]) +
        hCoefficients_nT[1][1] * sin(sphericalPosition_GeoCent_m[1])) *
           sin(sphericalPosition_GeoCent_m[2]));

  return GCONST_TRUE;
}