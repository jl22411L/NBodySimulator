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
/* None */

/* Structure Include */
/* None */
/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GRand/GRand.h"

int main(void)
{
  /* Declare local variables */
  FILE *p_outputFile;
  int   i;

  p_outputFile = fopen("data.csv", "w");

  fprintf(p_outputFile, "uniformDistributed,gaussianDistributed\n");

  for (i = 0; i < 100000; i++)
  {
    fprintf(p_outputFile,
            "%lf,%lf\n",
            GRand_uniformDistributon(),
            GRand_gaussianDistribution(5, 10));
  }

  fclose(p_outputFile);

  return GCONST_EXIT_SUCCESS;
}
