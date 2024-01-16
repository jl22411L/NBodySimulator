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

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 *  @description: Sets inputted Data to zero
 *
 *  @param[in]    p_data
 *                Pointer to the data that will have its memory be set to zero
 *
 * @param[in]     dataType
 *                Data type of data thats memory will be set to zero.
 *
 */
#define GZero(p_data, dataType) (memset(p_data, 0, sizeof(dataType)))

#ifdef __cplusplus
}
#endif

#endif /* H_GLOG_H */
