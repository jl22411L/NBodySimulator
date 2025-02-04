/*!
 *    @File:         Igrf_checkTolerances.c
 *
 *    @Brief:        Function which makes sure tolerances of the co-latitude are
 *                   acceptable to avoid having a singularity.
 *
 *    @Date:         01/02/2025
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "Igrf/ConstantDefs/Igrf_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int Igrf_checkTolerances(double *p_sphericalSecondaryBodyPosition_GeoCent_m_in)
{
  /* Declare local variables */
  /* None */

  /* Check latitude is not at poles to avoid singularity */
  if (*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) <=
          IGRF_COLATITUDE_ZERO_TOLERANCE_RAD &&
      *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) >= 0)
  {
    *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) +=
        IGRF_COLATITUDE_ZERO_TOLERANCE_RAD;
  }
  else if (*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) >=
               GCONST_PI - IGRF_COLATITUDE_ZERO_TOLERANCE_RAD &&
           *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) <= GCONST_PI)
  {
    *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) -=
        IGRF_COLATITUDE_ZERO_TOLERANCE_RAD;
  }
  else if (*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) < 0)
  {
    GError("Elevation is invalid: "
           "*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) "
           "= %lf",
           *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2));
  }
  else if (*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) > GCONST_PI)
  {
    GError("Elevation is invalid: "
           "*(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2) "
           "= %lf",
           *(p_sphericalSecondaryBodyPosition_GeoCent_m_in + 2));
  }

  return GCONST_TRUE;
}