/*!
 *    @File:         JamSail_Constants.h
 *
 *    @Brief:        Header file containing all the constants required by
 *                   JamSail's ADCS.
 *
 *    @Date:         01/03/2025
 *
 */

#ifndef H_JAMSAIL_CONSTANTS_H
#define H_JAMSAIL_CONSTANTS_H

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------ *
 * LIBRARY INCLUDES
 * ------------------------------------------------------------------------ */

#include <string.h>

#include "JamSail_Constants.h"

/* ------------------------------------------------------------------------ *
 * CONSTANT DEFINES
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Generic constant which is used to represent a true state.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_TRUE             (1)

/*!
 * @brief       Generic constant which is used to represent a false state.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GCONST_FALSE            (0)

/* ------------------------------------------------------------------------ *
 * MACRO DEFINES
 * ------------------------------------------------------------------------ */

/*!
 * @brief         Generic macro which will set inputted Data to zero
 *
 * @param[in]     p_data
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
#endif /* H_JAMSAIL_CONSTANTS_H */