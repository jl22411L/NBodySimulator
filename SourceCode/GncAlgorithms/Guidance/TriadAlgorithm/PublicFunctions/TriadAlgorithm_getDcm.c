/*
 *    @File:         Triad_getDcm.c
 *
 *    @Brief:        Function which returns a Direction Cosine Matrix of the
 *                   attitude.
 *
 *    @Date:         03/07/2024
 *
 */

#include <stdint.h>

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

int TriadAlgorithm_getDcm(double *p_vector1_bod_in,
                          double *p_vector1_fix_in,
                          double *p_vector2_bod_in,
                          double *p_vector2_fix_in,
                          double *p_dcm_fixToBod_out)
{
  /*
   * Declare Local Variables. Note that the buffers for the vectors are so that
   *                          the input vectors values don't change. As we only
   *                          need the unit vectors, their unit vectors are
   *                          outputted to the buffers to be used in the
   *                          algorithm.
   */
  double  bodToIntermediateDcm[3][3];
  double  intermediateToFixDcm[3][3];
  double  bodToFix[3][3];
  double  vector1Buffer_bod[3];
  double  vector1Buffer_fix[3];
  double  vector2Buffer_bod[3];
  double  vector2Buffer_fix[3];
  double  bodVectorBuffer[3];
  double  fixVectorBuffer[3];
  uint8_t i;

  /* Clear Variables */
  GZero(p_dcm_fixToBod_out, double[3][3]);
  GZero(&bodToIntermediateDcm[0], double[3][3]);
  GZero(&intermediateToFixDcm, double[3][3]);
  GZero(&bodToFix, double[3][3]);
  GZero(&bodVectorBuffer[0], double[3]);
  GZero(&fixVectorBuffer[0], double[3]);
  GZero(&vector1Buffer_bod[0], double[3]);
  GZero(&vector1Buffer_fix[0], double[3]);
  GZero(&vector2Buffer_bod[0], double[3]);
  GZero(&vector2Buffer_fix[0], double[3]);

  /* Find the unit vector of the input vectors */
  GMath_findUnitVector(p_vector1_bod_in, &vector1Buffer_bod[0]);
  GMath_findUnitVector(p_vector1_fix_in, &vector1Buffer_fix[0]);
  GMath_findUnitVector(p_vector2_bod_in, &vector2Buffer_bod[0]);
  GMath_findUnitVector(p_vector2_fix_in, &vector2Buffer_fix[0]);

  /* Load the first vector into the intermediate DCM's*/
  for (i = 0; i < 3; i++)
  {
    bodToIntermediateDcm[i][0] = vector1Buffer_bod[i];
    intermediateToFixDcm[0][i] = vector1Buffer_fix[i];
  }

  /* Find the cross produce between the two vectors into buffers */
  GMath_crossProduct(&vector1Buffer_bod[0],
                     &vector2Buffer_bod[0],
                     &bodVectorBuffer[0]);

  GMath_crossProduct(&vector1Buffer_fix[0],
                     &vector2Buffer_fix[0],
                     &fixVectorBuffer[0]);

  /* Find the unit vectors of the cross produce */
  GMath_findUnitVector(&bodVectorBuffer[0], &bodVectorBuffer[0]);
  GMath_findUnitVector(&fixVectorBuffer[0], &fixVectorBuffer[0]);

  /* Load the buffers into DCM's */
  for (i = 0; i < 3; i++)
  {
    bodToIntermediateDcm[i][1] = bodVectorBuffer[i];
    intermediateToFixDcm[1][i] = fixVectorBuffer[i];
  }

  /* Find the cross product between the first vector and the buffer and load
   * results into buffer */
  GMath_crossProduct(&vector1Buffer_bod[0],
                     &bodVectorBuffer[0],
                     &bodVectorBuffer[0]);

  GMath_crossProduct(&vector1Buffer_fix[0],
                     &fixVectorBuffer[0],
                     &fixVectorBuffer[0]);

  /* Load the buffer into DCM's */
  for (i = 0; i < 3; i++)
  {
    bodToIntermediateDcm[i][2] = bodVectorBuffer[i];
    intermediateToFixDcm[2][i] = fixVectorBuffer[i];
  }

  /* Multiply the DCM's together and output into the output DCM */
  GMath_matMul3x3by3x3(&bodToIntermediateDcm[0][0],
                       &intermediateToFixDcm[0][0],
                       &bodToFix[0][0]);

  GMath_invMat(&bodToFix[0][0], p_dcm_fixToBod_out, 3);

  return GCONST_TRUE;
}
