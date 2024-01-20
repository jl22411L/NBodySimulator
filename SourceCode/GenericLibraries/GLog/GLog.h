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
 
/*
 *    @Description: Outputs a msg to the console
 *
 */
#define GMsg(...) (printf("[MSG] ")),    \
                  (printf(__VA_ARGS__)), \
                  (printf("\n"))

/* --------------------------------- GError --------------------------------- */

/*
 *    @Description: Throw an error, outputting the file and line of the file.
 *
 */
#define GError(...) (printf("\n[ERR] ")),                      \
                    (printf(__VA_ARGS__)),                     \
                    (printf("\n")),                            \
                    (printf("[...] \n")),                      \
                    (printf("[MSG]    FILE: %s\n", __FILE__)), \
                    (printf("[MSG]    LINE: %d\n", __LINE__)), \
                    (printf("[...] \n")),                      \
                    (printf("[...] exiting programme...\n")),  \
                    (exit(GCONST_EXIT_FAILURE))

// clang-format on

#ifdef __cplusplus
}
#endif

#endif /* H_GLOG_H */
