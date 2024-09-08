/*
 *    @File:         GUtilities_PrivateFunctions.h
 *
 *    @Brief:        Contains Private Functions for GUtilities
 *
 *    @Date:         07/08/2024
 *
 */

#ifndef H_GUTILITIES_PRIVATEFUNCTIONS_H
#define H_GUTILITIES_PRIVATEFUNCTIONS_H

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
 * @brief       Function which catches a SIGINT and will set runSimStateus
 *              member in GUtilities struct to GCONST_FALSE to stop simulation
 *              but still allow termination functions to proceed.
 *
 * @param[in]   signum_in
 *              Signal input
 *
 * @return      Upon a successful completion, the fucntion will return a
 *              GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern void GUtilities_sigintHandle(int signum_in);

#ifdef __cplusplus
}
#endif
#endif /* H_GUTILITIES_PRIVATEFUNCTIONS_H */
