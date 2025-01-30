/*
 *    @File:         GArchive_Constants.h
 *
 *    @ Brief:       Constants for GArchive
 *
 *    @ Date:        05/02/2024
 *
 */

#ifndef H_GARCHIVE_CONSTANT_H
#define H_GARCHIVE_CONSTANT_H

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
 * @brief       Integer which represents the maximum size of the buffer which
 *              will hold a directory to an archive.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GARCHIVE_DIRECTORY_BUFFER    (512)

/*!
 * @brief       Buffer which holds the directory to the Data.csv file of the
 *              archive. /Data.csv is 9 charecters, hence this constant should
 *              be at least GARCHIVE_DIRECTORY_BUFFER + 9.
 *
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GARCHIVE_DATA_FILE_BUFFER    (GARCHIVE_DIRECTORY_BUFFER + 10)

/*!
 * @brief       Integer representing the maximum number of columns that can be
 *              archived.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GARCHIVE_MAX_COLS            (128)

/*!
 * @brief       Integer representing the maximum length of a column name.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GARCHIVE_MAX_COL_NAME_BUFFER (1024)

#ifdef __cplusplus
}
#endif

#endif /*  H_GARCHIVE_CONSTANT_H */
