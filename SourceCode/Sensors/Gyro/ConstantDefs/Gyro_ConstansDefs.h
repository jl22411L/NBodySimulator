/*!
 *    @File:         Gyro_ConstansDefs.h
 *
 *    @Brief:        Header file containing constants for Gyro model.
 *
 *    @Date:         05/02/2025
 *
 */

#ifndef H_GYRO_CONSTANSDEFS_H
#define H_GYRO_CONSTANSDEFS_H

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
#define GYRO_MAX_SENSOR_NAME_BUFFER  (64)

/*!
 * @brief       Max buffer size for storing the directory of the archive.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GYRO_ARCHIVE_FILENAME_BUFFER (128)

#ifdef __cplusplus
}
#endif
#endif /* H_GYRO_CONSTANSDEFS_H */