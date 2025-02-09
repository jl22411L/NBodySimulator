/*!
 *    @File:         GRand_gaussianDistribution.c
 *
 *    @Brief:        Function which will output a gaussian distributed random
 *                   number.
 *
 *    @Date:         09/02/2025
 *
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* Function Includes */
#include "GRand/PublicFunctions/GRand_PublicFunctions.h"

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

double GRand_gaussianDistribution(double mean_in, double standardDeviation_in)
{
  /* Declare local variables */
  static double storedGaussianRandomNumber;
  static int8_t randomNumbersGenerated;
  double        uniformRandomNumber1;
  double        uniformRandomNumber2;
  double        magnitude;
  double        angle_rad;

  /*!
   * The function naturally generates two gaussian randomoly distributed numbers
   * from two uniform numbers. The process intertwines the two uniform
   * distributed numbers. You could just discard one of the gaussian numbers
   * and only return 1, which would make the function more readable, however
   * this will hald the period of the pseudo random number generator. Hence,
   * this process was followed instead. Essentially a static variable stores one
   * of the random numbers for the next call. A static flag also keeps track on
   * if the variable is stored or not.
   */
  if (randomNumbersGenerated == GCONST_FALSE)
  {
    /* Find two uniform distributed random number */
    uniformRandomNumber1 = GRand_uniformDistributon();
    uniformRandomNumber2 = GRand_uniformDistributon();

    /* Confirm first random number is not equal to 0.0 or 1.0 */
    while (uniformRandomNumber1 >= 1.0 || uniformRandomNumber1 <= 0.0)
    {
      uniformRandomNumber1 = GRand_uniformDistributon();
    }

    /* Find the magnitude of the gaussian random number */
    magnitude = standardDeviation_in * sqrt(-2 * log(uniformRandomNumber1));

    /* Find the angle on the polar scale of the gaussian random number */
    angle_rad = 2 * GCONST_PI * uniformRandomNumber2;

    /* Find the gaussian random number to be stored */
    storedGaussianRandomNumber = magnitude * cos(angle_rad) + mean_in;

    /* Set flag to true indicating that random numbers have been generater */
    randomNumbersGenerated = GCONST_TRUE;

    /* Return the other gaussian number */
    return magnitude * sin(angle_rad) + mean_in;
  }
  else
  {

    /* Reset flag to indicate that new random numbers need to be generater */
    randomNumbersGenerated = GCONST_FALSE;

    return storedGaussianRandomNumber;
  }
}