/*
 *    @File:         main.c
 *
 *    @ Brief:       ModuleUnitTest
 *
 *    @ Date:        02/03/2024
 *
 */

#include <math.h>
#include <stdio.h>

/* Function Includes */
#include "Igrf/PublicFunctions/Igrf_PublicFunctions.h"

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLegPoly/PublicFunctions/GLegPoly_PublicFunctions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

#define step 1e-10

int main(void)
{
  /* Declare local variables */
  Igrf_Params igrf_params;
  double      sphericalCoordinates_GeoCen_m[3];
  double      primaryBodyRadius_m = 6378000;
  double      simTime_s           = 0.0;
  double      magneticFieldVector_Ned_nT[3];
  int         i;
  int         j;
  int         k;
  int         l;
  FILE       *p_outputFile;

  /* Clear Arrays */
  GZero(&igrf_params, Igrf_Params);
  GZero(&(sphericalCoordinates_GeoCen_m[0]), double[3]);

  Igrf_init(&igrf_params, "Parameters/IgrfParameters.ini", 13, 13);

  p_outputFile = fopen("Data.csv", "w");
  fprintf(
      p_outputFile,
      "sphericalCoordinates_GeoCen_m[0],sphericalCoordinates_GeoCen_m[1],"
      "sphericalCoordinates_GeoCen_m[2],simTime_s,magneticFieldVector_Ned_"
      "nT[0],magneticFieldVector_Ned_nT[1],magneticFieldVector_Ned_nT[2]\n");

  for (i = 0; i < 31; i++)
  {
    for (j = 0; j < 5; j++)
    {
      for (k = 0; k < 5; k++)
      {
        for (l = 0; l < 5; l++)
        {
          sphericalCoordinates_GeoCen_m[0] = 6471000.0 + ((double)i) * 20000;
          sphericalCoordinates_GeoCen_m[1] =
              (-180.0 + ((double)j) * 360 / 5) * GCONST_DEG_TO_RAD;
          sphericalCoordinates_GeoCen_m[2] =
              (-90.0 + ((double)k) * 180 / 5) * GCONST_DEG_TO_RAD;
          simTime_s = 1577836800.0 +
                      ((double)l) * (GCONST_YEARS_TO_SECONDS_CONVERSION) / 5;

          Igrf_step(&igrf_params,
                    &(sphericalCoordinates_GeoCen_m[0]),
                    6371000.0,
                    simTime_s,
                    &(magneticFieldVector_Ned_nT[0]));

          fprintf(p_outputFile,
                  "%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
                  sphericalCoordinates_GeoCen_m[0],
                  sphericalCoordinates_GeoCen_m[1],
                  sphericalCoordinates_GeoCen_m[2],
                  simTime_s,
                  magneticFieldVector_Ned_nT[0],
                  magneticFieldVector_Ned_nT[1],
                  magneticFieldVector_Ned_nT[2]);
        }
      }
    }
  }

  fclose(p_outputFile);

  return GCONST_EXIT_SUCCESS;
}
