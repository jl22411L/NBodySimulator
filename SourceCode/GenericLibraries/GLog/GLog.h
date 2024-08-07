/*
 *    @File:         GError.h
 *
 *    @ Brief:       This contains macros for logging msgs
 *
 *    @ Time:        16/12/2023
 *
 */

#ifndef H_GLOG_H
#define H_GLOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

// clang-format off

/* ---------------------------------- GMsg ---------------------------------- */
 
/*!
 * @brief     Outputs a msg to the console
 */
#define GLog(...) (printf("[MSG] ")),    \
                  (printf(__VA_ARGS__)), \
                  (printf("\n"))

/* --------------------------------- GError --------------------------------- */

/*!
 * @brief     This will highlight that an error has occured but won't stop the
 *            running of the code. This should be used in tandem with GError
 *            to allow for neater formatting on the terminal.
 */
#define GWarn(...) (printf("\033[0;33[WRN]\033[0m %s: %d \n", __FILE__, __LINE__)), \
                   (printf("\033[0;33[WRN]\033[0m ")),                              \
                   (printf(__VA_ARGS__)),                           \
                   (printf("\n"))                                   

/*!
 * @brief     Throw an error, outputting the file and line of the file.
 *
 */
#define GError(...) (printf("\033[0;31[ERR]\033[0m %s: %d \n", __FILE__, __LINE__)), \
                    (printf("\033[0;31[ERR]\033[0m ")),                              \
                    (printf(__VA_ARGS__)),                           \
                    (printf("\n")),                                  \
                    (printf("\033[0;31[ERR]\033[0m exiting programme...\n")),        \
                    (exit(GCONST_EXIT_FAILURE))

#define GAssess(Test) (if(Test != GCONST_TRUE)),                               \
                      ({GError("Function failed to complete successfully");})

// clang-format on

#ifdef __cplusplus
}
#endif

#endif /* H_GLOG_H */
