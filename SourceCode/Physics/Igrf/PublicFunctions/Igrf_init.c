/*
 *    @File:         Igrf_init.c
 *
 *    @Brief:        Initialises the Igrf library by loading all the parameters
 *                   for the model.
 *
 *    @Date:         11/09/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "Igrf/PrivateFunctions/Igrf_PrivateFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int Igrf_init(Igrf_Params *p_igrf_params_out,
              const char  *p_paramsFilePath_in,
              uint8_t      nMaxDegree_in,
              uint8_t      igrfIteration_in)
{
  /* Define local variables */
  /* None */

  /* Load parameters into Igrf_Params struct */
  Igrf_loadParams(p_igrf_params_out,
                  p_paramsFilePath_in,
                  nMaxDegree_in,
                  igrfIteration_in);

  /* Apply Schmidt-Quasi Normalisation to coefficients */
  Igrf_applyNormalisation(p_igrf_params_out);

  return GCONST_TRUE;
}
