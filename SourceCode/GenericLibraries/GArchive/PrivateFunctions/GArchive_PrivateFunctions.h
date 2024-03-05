/*
 *    @File:         GArchive_PrivateFunctions.h
 *
 *    @ Brief:       Header file containing the private functions for GArchive
 *
 *    @ Date:        05/02/2024
 *
 */

#ifndef H_GARCHIVE_PRIVATEFUNCTIONS_H
#define H_GARCHIVE_PRIVATEFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief          Adds column to the archive struct which will be outputted in
 *                 the archive struct. This function is called when nColsAdd_in
 *                 is greater then 1.
 *
 * @param[in,out]  p_archive_inout
 *                 Pointer to GArchive struct which will the column names will
 *                 be written towards.
 *
 * @param[in]      p_colName_in
 *                 Name of column to add to archive struct.
 *
 * @param[in]     nColsAdd_in
 *                Number of columns to add. If this is greater than 1, it is
 *                assumed that an array is being added and will have the
 *                appropraite index added. Whether it is 2D or 1D depends on the
 *                nRowsAdd_in input.
 *
 * @param[in]     nRowsAdd_in
 *                Number of rows to add. If this is greater than 1, it is
 *                assumed that a 2D array is being added and will have an
 *                appropriate index added.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE
 */
extern int GArchive_addColArray(
    GArchive   *p_archive_inout,
    const char *p_colName_in,
    uint8_t     nColsAdd_in,
    uint8_t     nRowsAdd_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GARCHIVE_PRIVATEFUNCTIONS_H */
