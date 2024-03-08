/*
 *    @File:         GMath_crossProduct.c
 *
 *    @ Brief:       Finds the cross product of vectos {a} & {b} ({a}x{b}={c})
 *
 *    @ Date:        08/03/2024
 *
 */

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GMath_crossProduct(
    double *p_vectorA_in,
    double *p_vectorB_in,
    double *p_vectrocC_out)
{
  /* Declaring local variables */
  double aVectorX;
  double aVectorY;
  double aVectorZ;
  double bVectorX;
  double bVectorY;
  double bVectorZ;

  /* Find the components of the A vector */
  aVectorX = *(p_vectorA_in + 0);
  aVectorY = *(p_vectorA_in + 1);
  aVectorZ = *(p_vectorA_in + 2);

  /* Find the components of the A vector */
  bVectorX = *(p_vectorB_in + 0);
  bVectorY = *(p_vectorB_in + 1);
  bVectorZ = *(p_vectorB_in + 2);

  /* Find cross product and output to C vector */
  *(p_vectrocC_out + 0) = aVectorY * bVectorZ - aVectorZ * bVectorY;
  *(p_vectrocC_out + 1) = aVectorZ * bVectorX - aVectorX * bVectorZ;
  *(p_vectrocC_out + 2) = aVectorX * bVectorY - aVectorY * bVectorX;

  return GCONST_TRUE;
}
