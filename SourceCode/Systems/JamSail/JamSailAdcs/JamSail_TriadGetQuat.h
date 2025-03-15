/*!
 *    @File:         JamSail_Adcs.h
 *
 *    @Brief:        Header file containing all the function definitions for
 *                   JamSail's ADCS.
 *
 *    @Date:         01/03/2025
 *
 */

#ifndef H_JAMSAIL_ADCS_H
#define H_JAMSAIL_ADCS_H

#ifdef __cplusplus
extern "C" {
/*!
 * LIBRARY INCLUDES
 * GENERIC CONSTANTS
 * GENERIC MACROS
 * GENERIC MATH FUNCTIONS
 * ADCS DETERMINATION
 * ADCS CONTROL
 */

#include <math.h>
#include <stdint.h>
#include <string.h>

/* ------------------------------------------------------------------------ *
 * GENERIC MATH FUNCTIONS
 * ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ *
 * ADCS DETERMINATION
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Triad algorithm which finds the quaternion from the inertial
 *              frame to the body frame. It takes 2 vectors which have been both
 *              measured in the body frame as well as the fixed frame. The first
 *              vector should be the one which is more accurate and has less
 *              noise for better performance.
 *
 * @param[in]   p_vector1_bod_in
 *              Pointer to vector 1 measured in the body frame.
 *
 * @param[in]   p_vector1_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[in]   p_vector2_bod_in
 *              Pointer to vector 2 measured in the body frame.
 *
 * @param[in]   p_vector2_fix_in
 *              Pointer to vector 1 measured in the fixed frame.
 *
 * @param[out]  p_quat_fixToBod_out
 *              Pointer containing address of quaternion which contains the
 *              transformation from fixed frame to body frame.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
int JamSail_TriadGetQuat(double *p_vector1_Bod_in,
                         double *p_vector1_Fix_in,
                         double *p_vector2_Bod_in,
                         double *p_vector2_Fix_in,
                         double *p_quat_FixToBod_out)
{
  /*
   * Declare Local Variables. Note that the buffers for the vectors are so that
   *                          the input vectors values don't change. As we only
   *                          need the unit vectors, their unit vectors are
   *                          outputted to the buffers to be used in the
   *                          algorithm.
   */
  double  dcm_bodToFix[3][3];
  double  bodToIntermediateDcm[3][3];
  double  intermediateToFixDcm[3][3];
  double  vector1Buffer_bod[3];
  double  vector1Buffer_fix[3];
  double  vector2Buffer_bod[3];
  double  vector2Buffer_fix[3];
  double  bodVectorBuffer[3];
  double  fixVectorBuffer[3];
  uint8_t i;

  /* Clear Variables */
  GZero(&dcm_bodToFix[0][0], double[3][3]);
  GZero(p_quat_FixToBod_out, double[4]);
  GZero(&bodToIntermediateDcm[0], double[3][3]);
  GZero(&intermediateToFixDcm, double[3][3]);
  GZero(&bodVectorBuffer[0], double[3]);
  GZero(&fixVectorBuffer[0], double[3]);
  GZero(&vector1Buffer_bod[0], double[3]);
  GZero(&vector1Buffer_fix[0], double[3]);
  GZero(&vector2Buffer_bod[0], double[3]);
  GZero(&vector2Buffer_fix[0], double[3]);

  /* Find the unit vector of the input vectors */
  GMath_findUnitVector(p_vector1_Bod_in, &vector1Buffer_bod[0]);
  GMath_findUnitVector(p_vector1_Fix_in, &vector1Buffer_fix[0]);
  GMath_findUnitVector(p_vector2_Bod_in, &vector2Buffer_bod[0]);
  GMath_findUnitVector(p_vector2_Fix_in, &vector2Buffer_fix[0]);

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
                       &dcm_bodToFix[0][0]);

  /* Convert the dcm to a quaternion */
  GMath_dcm2Quat(&dcm_bodToFix[0][0], p_quat_FixToBod_out);

  return GCONST_TRUE;
}

/* ------------------------------------------------------------------------ *
 * ADCS CONTROL
 * ------------------------------------------------------------------------ */

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_ADCS_H */