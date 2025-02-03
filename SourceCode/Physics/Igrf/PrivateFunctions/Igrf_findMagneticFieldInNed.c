/*
 *    @File:         Igrf_findMagneticFieldInNed.c
 *
 *    @Brief:        Function which calcaultes the magnetic field components.
 *
 *    @Date:         22/10/2024
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Function Includes */
#include "Igrf/PrivateFunctions/Igrf_PrivateFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int Igrf_findMagneticFieldInNed(double      *p_magneticFieldVector_ned_out,
                                double      *p_secondaryBodyPosSph_geoCent_m_in,
                                double      *p_associatedLegPoly_in,
                                double      *p_assocaitedLegPolyDerivitive_in,
                                double       primaryBodyRadius_m_in,
                                double       simTime_s_in,
                                Igrf_Params *p_igrf_params_in)
{
  /* Declare local variables */
  double  gCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double  hCoefficients_nT[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1];
  double  factor;
  double  secondaryBodyRadialDistance_m;
  double  secondaryBodyLong_rad;
  double  secondaryBodyLat_rad;
  double  radialComponent;
  double  latitudeComponent;
  double  longitudeComponent;
  uint8_t n;
  uint8_t m;
  uint8_t k;

  /* Clear buffers */
  GZero(&gCoefficients_nT[0][0],
        double[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1]);
  GZero(&hCoefficients_nT[0][0],
        double[IGRF_MAX_DEGREE + 1][IGRF_MAX_DEGREE + 1]);
  GZero(p_magneticFieldVector_ned_out, double[3]);

  /* Decompose position of secondary body */
  secondaryBodyRadialDistance_m = *(p_secondaryBodyPosSph_geoCent_m_in + 0);
  secondaryBodyLong_rad         = *(p_secondaryBodyPosSph_geoCent_m_in + 1);
  secondaryBodyLat_rad          = *(p_secondaryBodyPosSph_geoCent_m_in + 2);

  /* Fing the gaussian coefficients for the current sim time */
  Igrf_findCoefficients(&gCoefficients_nT[0][0],
                        &hCoefficients_nT[0][0],
                        simTime_s_in,
                        p_igrf_params_in);

  /*!
   * Find the spherical harmonics of the magnetic field.
   *
   * [Ref: Mathematical modeling and simulation of the earth’s magnetic
   field: A
   *       comparative study of the models on the spacecraft attitude control
   *       application - M. Navabi, M. Barati]
   *
   * NOTE: The reference has made an error on what it calls longitude and
   *       latitude.
   */
  for (n = 1; n <= p_igrf_params_in->nMaxDegree; n++)
  {
    /* Set initial values for magnetic field components */
    radialComponent    = 0;
    latitudeComponent  = 0;
    longitudeComponent = 0;

    for (m = 0; m <= n; m++)
    {
      /* Iterate through the different orders of the spherical harmonics */
      radialComponent +=
          ((gCoefficients_nT[n][m] * cos((double)m * secondaryBodyLong_rad) +
            hCoefficients_nT[n][m] * sin((double)m * secondaryBodyLong_rad)) *
           (*(p_associatedLegPoly_in + (IGRF_MAX_DEGREE + 1) * n + m)));

      longitudeComponent +=
          ((((double)m) * gCoefficients_nT[n][m] *
                sin((double)m * secondaryBodyLong_rad) -
            ((double)m) * hCoefficients_nT[n][m] *
                cos((double)m * secondaryBodyLong_rad)) *
           (*(p_associatedLegPoly_in + (IGRF_MAX_DEGREE + 1) * n + m)));

      latitudeComponent +=
          ((-gCoefficients_nT[n][m] * cos((double)m * secondaryBodyLong_rad) -
            hCoefficients_nT[n][m] * sin((double)m * secondaryBodyLong_rad)) *
           (*(p_assocaitedLegPolyDerivitive_in + (IGRF_MAX_DEGREE + 1) * n +
              m)));
    }

    /* Find the factor */
    factor = pow(primaryBodyRadius_m_in / secondaryBodyRadialDistance_m,
                 (double)n + 2.0);

    /* Add result from order to output */
    *(p_magneticFieldVector_ned_out + 0) += latitudeComponent * factor;
    *(p_magneticFieldVector_ned_out + 1) += longitudeComponent * factor;
    *(p_magneticFieldVector_ned_out + 2) +=
        radialComponent * ((double)n + 1.0) * factor;
  }

  /* Scale output */
  *(p_magneticFieldVector_ned_out + 0) *= -sin(secondaryBodyLat_rad);
  *(p_magneticFieldVector_ned_out + 1) *= 1 / sin(secondaryBodyLat_rad);
  *(p_magneticFieldVector_ned_out + 2) *= -1;

  return GCONST_TRUE;
}
