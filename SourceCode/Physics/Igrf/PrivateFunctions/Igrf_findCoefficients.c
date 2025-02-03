/*
 *    @File:         Igrf_findCoefficients.c
 *
 *    @Brief:        Function which finds coefficients
 *
 *    @Date:         23/10/2024
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int Igrf_findCoefficients(double      *p_gCoefficients_nT_out,
                          double      *p_hCoefficients_nT_out,
                          double       simTime_s_in,
                          Igrf_Params *p_igrf_params_in)
{
  /* Declare local variables */
  double  timeSinceEpoch_s;
  uint8_t n;
  uint8_t m;

  /* Check if simTime is within time of igrf iteration and if log a warning */
  if (simTime_s_in >= p_igrf_params_in->endUnixTime_s ||
      simTime_s_in < p_igrf_params_in->startUnixTime_s)
  {
    GWarn("simTime is outside the range for IGRF. \n"
          "simTime_s_in = %lf \n"
          "startUnixTime_s = %lf \n"
          "endUnixTime_s = %lf \n"
          "igrfIteration = %d  \n",
          simTime_s_in,
          p_igrf_params_in->startUnixTime_s,
          p_igrf_params_in->endUnixTime_s,
          p_igrf_params_in->igrfIteration);
  }

  /* Find the time since epoch */
  timeSinceEpoch_s = simTime_s_in - p_igrf_params_in->startUnixTime_s;

  /* Find coefficients */
  for (n = 1; n <= p_igrf_params_in->nMaxDegree; n++)
  {
    for (m = 0; m <= n; m++)
    {
      /* Find g coefficients */
      *(p_gCoefficients_nT_out + n * (IGRF_MAX_DEGREE + 1) + m) =
          p_igrf_params_in->gEpochCoefficients_nT[n][m] +
          timeSinceEpoch_s *
              (p_igrf_params_in->gLinearRateCoefficients_nTs[n][m]);

      /* Find h coefficients */
      *(p_hCoefficients_nT_out + n * (IGRF_MAX_DEGREE + 1) + m) =
          p_igrf_params_in->hEpochCoefficients_nT[n][m] +
          timeSinceEpoch_s *
              (p_igrf_params_in->hLinearRateCoefficients_nTs[n][m]);
    }
  }

  return GCONST_TRUE;
}
