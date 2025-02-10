/*!
 *    @File:         GRand_globalVariables.c
 *
 *    @Brief:        C File which contains the global variables required for
 *                   library.
 *
 *    @Date:         08/02/2025
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

/*!
 * @brief         Global variable used to keep track of the input in the linear
 *                congruential generator. If a specific seed is to be set for
 *                the random number generator, it should be set on this
 *                variable.
 *
 * @frame         N/A
 * @unit          N/A
 */
uint64_t randomNumberInput;
