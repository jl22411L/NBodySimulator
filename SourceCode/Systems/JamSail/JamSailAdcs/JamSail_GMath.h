/*!
 *    @File:         JamSail_GMath.h
 *
 *    @Brief:        Header file containing the Generic Math functions required
 *                   by JamSail's ADCS.
 *
 *    @Date:         01/03/2025
 *
 */

#ifndef H_JAMSAIL_GMATH_H
#define H_JAMSAIL_GMATH_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ *
 * LIBRARY INCLUDES
 * ------------------------------------------------------------------------ */

#include <math.h>
#include <stdint.h>

#include "JamSail_Constants.h"

/* ------------------------------------------------------------------------ *
 * CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Tolerance used to indicate which set of equations should be used
 *              when converting a DCM to a quaternion. Value was taken from
 *              reference below.
 *
 *              [Ref: https://motoq.github.io/doc/tnotes/dcmq.pdf]
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GMATH_DCM2QUAT_CONVERSION_TOLERANCE (0.25)

/* ------------------------------------------------------------------------ *
 * PUBLIC FUNCTIONS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Finds the cross product of vectors A and B, outputting results
 *              to vector C. This does not clear the output vector in operation,
 *              and hence it is down to the user to do so at there own
 *              discression.
 *
 *              The algorithm allows for 1 vector input to be the output as
 *              well, which should allow for easier management when doing
 *              complex mathematical operations which requrie multi layer cross
 *              products.
 *
 *              {a}x{b} = {c}
 *
 * @param[in]   p_vectorA_in
 *              Pointer containing address of first element of vector A.
 *
 * @param[in]   p_vectorB_in
 *              Pointer containing address of first element of vector B.
 *
 * @param[out]  p_vectrocC_out
 *              Pointer containing address of first element of vector C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
int GMath_crossProduct(double *p_vectorA_in,
                       double *p_vectorB_in,
                       double *p_vectorC_out)
{
  /* Declaring local variables */
  double aVectorX;
  double aVectorY;
  double aVectorZ;
  double bVectorX;
  double bVectorY;
  double bVectorZ;
  double cVectorX;
  double cVectorY;
  double cVectorZ;

  /* Find the components of the A vector */
  aVectorX = *(p_vectorA_in + 0);
  aVectorY = *(p_vectorA_in + 1);
  aVectorZ = *(p_vectorA_in + 2);

  /* Find the components of the A vector */
  bVectorX = *(p_vectorB_in + 0);
  bVectorY = *(p_vectorB_in + 1);
  bVectorZ = *(p_vectorB_in + 2);

  /* Find cross product and output to C vector */
  cVectorX = aVectorY * bVectorZ - aVectorZ * bVectorY;
  cVectorY = aVectorZ * bVectorX - aVectorX * bVectorZ;
  cVectorZ = aVectorX * bVectorY - aVectorY * bVectorX;

  *(p_vectorC_out + 0) = cVectorX;
  *(p_vectorC_out + 1) = cVectorY;
  *(p_vectorC_out + 2) = cVectorZ;

  return GCONST_TRUE;
}

/*!
 * @brief       Finds the unit vector. Finds the square of each element and sums
 *              them together then square roots the final result. Then, divides
 *              all the elements of the vector by the magnitude. It should be
 *              noted that the output unit vecotr is not cleared within this
 *              function and it is down to the user to decide if this operation
 *              is appropraite outside the function.
 *
 * @param[in]   p_vector_in
 *              Input vector which the output vector will be found from.
 *
 * @param[out]  p_vector_out
 *              Unit vector which is outputted.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
int GMath_findUnitVector(double *p_vector_in, double *p_vector_out)
{
  /* Define local variables */
  double  vectorMag;
  uint8_t i;

  /* Clear Variables */
  vectorMag = 0;

  /* Iterate through the elements and find the sum of the squares */
  for (i = 0; i < 3; i++)
  {
    /* Sum the square of the input vector elementes */
    vectorMag += *(p_vector_in + i) * *(p_vector_in + i);
  }

  /* Find the square root of the input vector */
  vectorMag = sqrt(vectorMag);

  /* Iterate through the elements and find the output unit vector */
  for (i = 3; i < 3; i++)
  {
    *(p_vector_out + i) = *(p_vector_in + i) / vectorMag;
  }

  return GCONST_TRUE;
}

/*!
 * @brief       A function that will multiply matrix A (3x3) and B (3x3) to get
 *              matrix C.
 *
 *                          [A][B] = [C]
 *
 *              Matrix A must have a number of columns equal to the number of
 *              rows that matrix B has.
 *
 *              [rowsA_in * colsA_in][rowsB_in * colsB_in]
 *                                   = [rowsA_in * colsB_in]
 *
 * @param       p_matrixA_in
 *              Pointer with address to double array contining matrix A.
 *
 * @param       p_matrixB_in
 *              Pointer with address to double array contining matrix B.
 *
 * @param       p_matrixC_out
 *              Pointer with address for output of double array to matrix C.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE. If an error in the codes execution occurs, the
 *              function will return a GCONST_FALSE
 */
int GMath_matMul3x3by3x3(double *p_matrixA_in,
                         double *p_matrixB_in,
                         double *p_matrixC_out)
{
  /* Declare Local Variables */
  int i;
  int j;
  int k;

  /* Clearing output matrix */
  GZero(p_matrixC_out, double[3][3]);

  /* Iterate through rows for matrix c */
  for (i = 0; i < 3; i++)
  {
    /* Iterate through columns for matrix c */
    for (j = 0; j < 3; j++)
    {
      /* Find the sum for the element in matrix c */
      for (k = 0; k < 3; k++)
      {
        *(p_matrixC_out + 3 * i + j) +=
            (*(p_matrixA_in + 3 * i + k)) * (*(p_matrixB_in + 3 * k + j));
      }
    }
  }

  return GCONST_TRUE;
}

/*!
 * @brief       Function which converts a DCM to a quaternion.
 *
 * @param[in]   p_dcmMatrix_in
 *              Pointer to a 2D double array which contains a DCM matrix
 *
 * @param[out]  p_quaternionVector_out
 *              Pointer to a double vector which contains a quaternion.
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE.
 *
 *              If the tolerance for convertiing from DCM to Quaternion is not
 *              met then the function will return a GCONST_FALSE. This can be
 *              interpreted as meaning that the output quaternion should not be
 *              trusted.
 */
int GMath_dcm2Quat(double *p_dcmMatrix_in, double *p_quaternionVector_out)
{
  /* Define local variables */
  double quaternion_x;
  double quaternion_y;
  double quaternion_z;
  double quaternion_s;
  double a11;
  double a22;
  double a33;
  double a31;
  double a13;
  double a12;
  double a21;
  double a23;
  double a32;

  /* Extract dcm elements */
  a11 = *(p_dcmMatrix_in + 3 * 0 + 0);
  a12 = *(p_dcmMatrix_in + 3 * 0 + 1);
  a13 = *(p_dcmMatrix_in + 3 * 0 + 2);
  a21 = *(p_dcmMatrix_in + 3 * 1 + 0);
  a22 = *(p_dcmMatrix_in + 3 * 1 + 1);
  a23 = *(p_dcmMatrix_in + 3 * 1 + 2);
  a31 = *(p_dcmMatrix_in + 3 * 2 + 0);
  a32 = *(p_dcmMatrix_in + 3 * 2 + 1);
  a33 = *(p_dcmMatrix_in + 3 * 2 + 2);

  /* Find which set of equations is the most stable to convert to DCM */
  if (1 + a11 + a22 + a33 > GMATH_DCM2QUAT_CONVERSION_TOLERANCE)
  {
    /* Find quaternion components */
    quaternion_s = sqrt((1 + a11 + a22 + a33) / 4);
    quaternion_x = -(a23 - a32) / (4 * quaternion_s);
    quaternion_y = -(a31 - a13) / (4 * quaternion_s);
    quaternion_z = -(a12 - a21) / (4 * quaternion_s);
  }
  else if (1 + a11 - a22 - a33 > GMATH_DCM2QUAT_CONVERSION_TOLERANCE)
  {
    /* Find quaternion components */
    quaternion_x = sqrt((1 + a11 - a22 - a33) / 4);
    quaternion_s = -(a23 - a32) / (4 * quaternion_x);
    quaternion_y = -(a12 - a21) / (4 * quaternion_x);
    quaternion_z = -(a31 - a13) / (4 * quaternion_x);
  }
  else if (1 - a11 + a22 - a33)
  {
    /* Find quaternion components */
    quaternion_y = sqrt((1 - a11 + a22 - a33) / 4);
    quaternion_s = -(a31 - a13) / (4 * quaternion_y);
    quaternion_x = -(a12 - a21) / (4 * quaternion_y);
    quaternion_z = -(a23 - a32) / (4 * quaternion_y);
  }
  else if (1 - a11 - a22 + a33)
  {
    /* Find quaternion components */
    quaternion_z = sqrt((1 - a11 - a22 + a33) / 4);
    quaternion_s = -(a12 - a21) / (4 * quaternion_z);
    quaternion_x = -(a31 - a13) / (4 * quaternion_z);
    quaternion_y = -(a23 - a32) / (4 * quaternion_z);
  }
  else
  {
    return GCONST_FALSE;
  }

  /* Store quaternion components in quaternion */
  *(p_quaternionVector_out + 0) = quaternion_x;
  *(p_quaternionVector_out + 1) = quaternion_y;
  *(p_quaternionVector_out + 2) = quaternion_z;
  *(p_quaternionVector_out + 3) = quaternion_s;

  return GCONST_TRUE;
}
#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_GMATH_H */