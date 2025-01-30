/*
 *    @File:         SunSensor_ConstDefs.h
 *
 *    @Brief:        Header file containing constant definitions for SunSensor
 *
 *    @Date:         11/11/2024
 *
 */

#ifndef H_SUNSENSOR_CONSTDEFS_H
#define H_SUNSENSOR_CONSTDEFS_H

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
 * @brief       Cosntant which defines the maximum buffer of the parameter for
 *              which the filename of the sensor is.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define SUNSENSOR_MAX_SENSOR_NAME_BUFFER  (64)

/*!
 * @brief       Max buffer size for storing the directory of the archive.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define SUNSENSOR_ARCHIVE_FILENAME_BUFFER (128)

#ifdef __cplusplus
}
#endif
#endif /* H_SUNSENSOR_CONSTDEFS_H */