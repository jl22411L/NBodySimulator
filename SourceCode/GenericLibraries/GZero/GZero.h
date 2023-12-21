/*
 *    @File:         GZero.h
 *
 *    @ Brief:       This memory to make it clean
 *
 *    @ Time:        17/12/2023
 *
 */

#ifndef H_ZERO_H
#define H_ZERO_H

#include <string.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

// clang-format off

/* ---------------------------------- GMsg ---------------------------------- */
 

/* --------------------------------- GError --------------------------------- */

/*
 *    @Description: Sets inputted Data to zero
 *
 */
#define GZero(p_data ,dataType) (memset(p_data, 0, sizeof(dataType)))

/*
 *    @Description: Clears Data of arrays to 0
 *
 */
#define GClear(p_data, n_elements ,dataType) (memset(p_data, 0, n_elements*sizeof(dataType)))

// clang-format on

#endif /* H_GLOG_H */
