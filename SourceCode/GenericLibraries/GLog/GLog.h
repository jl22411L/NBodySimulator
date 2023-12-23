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
#define GMsg(msg) (printf("[MSG] %s", msg))

/* --------------------------------- GError --------------------------------- */

/*
 *    @Description: Throw an error, outputting the file and line of the file.
 *
 */
#define GError(msg) (printf("\n[ERR] ERROR OCCURED:   %s\n", msg)), \
                    (printf("[...] \n")),                           \
                    (printf("[MSG]    FILE: %s\n", __FILE__)),      \
                    (printf("[MSG]    LINE: %d\n", __LINE__)),      \
                    (printf("[...] \n")),                           \
                    (printf("[...] exiting programme...\n")),          \
                    (exit(GCONST_EXIT_FAILURE))

// clang-format on

#endif /* H_GLOG_H */
