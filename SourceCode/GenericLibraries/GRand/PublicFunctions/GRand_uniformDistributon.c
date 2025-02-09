/*!
 *    @File:         GRand_uniformDistributon.c
 *
 *    @Brief:        Function which returns a uniformly distributed random
 *                   number.
 *
 *    @Date:         08/02/2025
 *
 */

#include <stdint.h>
#include <time.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GRand/ConstantDefs/GRand_Constants.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

double GRand_uniformDistributon()
{
  /* Declare local variables */
  extern uint64_t randomNumberInput;
  uint64_t        randomNumberOutput;
  long double     scaledRandomNumber;

  /* If the random number input is 0, then set it to current unix time */
  if (randomNumberInput == 0)
  {
    randomNumberInput = time(NULL);
  }

  /* Find the random number output */
  randomNumberOutput =
      ((GRAND_LINEAR_CONGRUENTIAL_GENERATORS_MULTIPLIER * randomNumberInput +
        GRAND_LINEAR_CONGRUENTIAL_GENERATORS_INCRIMENT) %
       GRAND_LINEAR_CONGRUENTIAL_GENERATORS_MODULUS);

  /* Scale the random number to be between 0.0 and 1.0 */
  scaledRandomNumber =
      ((long double)randomNumberOutput) /
      ((long double)GRAND_LINEAR_CONGRUENTIAL_GENERATORS_MODULUS);

  /* Check that scaled random number is not less than 0.0 */
  if (scaledRandomNumber < 0.0)
  {
    GError("Random number is less than 0.0. (scaledRandomNumber = %lf)",
           scaledRandomNumber);
  }

  /* Check that scaled random number is not greater than 1.0 */
  if (scaledRandomNumber > 1.0)
  {
    GError("Random number is greater than 1.0. (scaledRandomNumber = %lf)",
           scaledRandomNumber);
  }

  /* Step the random number */
  randomNumberInput = randomNumberOutput;

  return scaledRandomNumber;
}