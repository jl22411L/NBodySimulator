/*
 *    @File:         GMath_invMat.c
 *
 *    @ Brief:       Finds the inverse of a matrix
 *
 *    @ Date:
 *
 */

/* Function Includes */
#include "GMath/PrivateFunctions/GMath_PrivateFunctions.h"
#include "GMath/PublicFunctions/GMath_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GMath_invMat(double *p_inputMat_in, double *p_outputMat_out, int sideN_in)
{
  /* Defining Local variables */
  double inputColBuffer[GCONST_BUFFER_32];
  double resultColumnBuffer[GCONST_BUFFER_32];
  int    i;
  int    j;

  /* Clearing buffers */
  GZero(&inputColBuffer[0], double[GCONST_BUFFER_32]);
  GZero(&resultColumnBuffer[0], double[GCONST_BUFFER_32]);

  /* For each column of the matrix find the respective inverse column */
  for (i = 0; i < sideN_in; i++)
  {
    /* Find the result column for which to find the inv column of */
    for (j = 0; j < sideN_in; j++)
    {
      /* If j == i then along diagnol hence set to 1. Otherwise set to 0 */
      if (j == i)
      {
        resultColumnBuffer[j] = 1;
      }
      else
      {
        resultColumnBuffer[j] = 0;
      }
    }

    /* Find the column of the inverse matrix */
    GMath_invCol(
        p_inputMat_in,
        &resultColumnBuffer[0],
        &inputColBuffer[0],
        sideN_in);

    /* Load column buffer into output matrix */
    for (j = 0; j < sideN_in; j++)
    {
      *(p_outputMat_out + j * sideN_in + i) = inputColBuffer[j];
    }

    /* Clear buffer */
    GZero(&inputColBuffer[0], double[sideN_in]);
  }

  return GCONST_TRUE;
}
