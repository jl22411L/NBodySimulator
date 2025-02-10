/*!
 *    @File:         GRand_PublicFunctions.h
 *
 *    @Brief:        Header file which constains the public functions for
 *                   GRand library.
 *
 *    @Date:         09/02/2025
 *
 */

#ifndef H_GRAND_PUBLICFUNCTIONS_H
#define H_GRAND_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         This function returns a randomly generated which follows a
 *                gaussian distribution.
 *
 * @param[in]     mean_in
 *                Mean of the random number being generated.
 *
 * @param[in]     standardDeviation_in
 *                Standard deviation of the random numbers being generated.
 *
 * @return        Returns a random number following a gaussian distribution.
 *
 *                Note: The reason this function doesn't follow the convention
 *                      in the README and returns a random number is to make it
 *                      easier to use.
 */
extern double GRand_gaussianDistribution(double mean_in,
                                         double standardDeviation_in);

/*!
 * @brief         This function returns a randomly generated number using the
 *                linear congrutenial generator.
 *
 * @return        Returns a psedo random number between 0.0 and 1.0.
 *
 *                Note: The reason this function doesn't follow the convention
 *                      in the README and returns a random number is to make it
 *                      easier to use.
 */
extern double GRand_uniformDistributon();

#ifdef __cplusplus
}
#endif
#endif /* H_GRAND_PUBLICFUNCTIONS_H */