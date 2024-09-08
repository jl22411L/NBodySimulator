/*
 *    @File:         GArchive_PublicFunctions.h
 *
 *    @ Brief:       Header file which contains the public functions for
 *                   GArchive
 *
 *    @ Date:        28/01/2024
 *
 */

#ifndef H_GARCHIVE_PUBLICFUNCTIONS_H
#define H_GARCHIVE_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief           Adds column to the archive struct which will be outputted in
 *                  the archive folder.
 *
 * @param[in,out]   p_archive_inout
 *                  Pointer to GArchive struct which will the column names will
 *                  be written towards.
 *
 * @param[in]       p_colName_in
 *                  Name of column to add to archive struct.
 *
 * @param[in]       nColsAdd_in
 *                  Number of columns to add. If this is greater than 1, it is
 *                  assumed that an array is being added and will have the
 *                  appropraite index added. Whether it is 2D or 1D depends on
 *                  the nRowsAdd_in input.
 *
 * @param[in]       nRowsAdd_in
 *                  Number of rows to add. If this is greater than 1, it is
 *                  assumed that a 2D array is being added and will have an
 *                  appropriate index added.
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GArchive_addCol(
    GArchive   *p_archive_inout,
    const char *p_colName_in,
    uint8_t     nColsAdd_in,
    uint8_t     nRowsAdd_in);

/*!
 * @brief           Adds a value to archive struct which will be written to the
 *                  archive folder.
 *
 * @param[in]       p_archive_in
 *                  Pointer to archive to write the value too.
 *
 * @param[in]       archiveValue_in
 *                  Value to write to archive struct.
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GArchive_addVal(GArchive *p_archive_in, double archiveValue_in);

/*!
 * @brief           Checks if a file exists.
 *
 * @param[in]       p_filename
 *                  String containing the name of the file to check.
 *
 * @return          If GCONST_TRUE is returned, then file exists. If
 *                  GCONST_FALSE is returned then the file does not exist.
 */
extern int GArchive_checkFileExists(const char *p_filename_in);

/*!
 * @brief           Closes the archive file and sets all members to zero.

 * @param[in]       p_archive_in
 *                  Pointer to archive struct
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GArchive_close(GArchive *p_archive_in);

/*!
 * @brief           This function will create the archive folder for which the
 *                  data will be saved in.
 *
 * @param[in]       p_archiveDataFilename_in
 *                  String containting path to which the archive file.
 *                  (e.g ArchiveData/RigidBody)
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int
    GArchive_init(GArchive *p_archive_in, char *p_archiveDataFilename_in);

/*!
 * @brief           Writes the data in the archive struct to the Archive folder.
 *
 * @param[in]       p_archive_in
 *                  Pointer to the archive struct which contains data to be
 *                  archived.
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GArchive_writeLine(GArchive *p_archive_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GARCHIVE_PUBLICFUNCTIONS_H */
