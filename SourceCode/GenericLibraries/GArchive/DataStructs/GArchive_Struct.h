/*
 *    @File:         GArchive_Struct.h
 *
 *    @ Brief:       Containts struct for GArchive
 *
 *    @ Date:        05/02/2024
 *
 */

#ifndef H_GARCHIVE_STRUCT_H
#define H_GARCHIVE_STRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
#include "GArchive/ConstantDefs/GArchive_Constants.h"

/* Generic Libraries */
/* None */

/*!
 * @brief This struct will store the information required to archive a struct.
 *        This struct should be inserted as a member in the struct you want to
 *        archive.
 */
typedef struct GArchive_Struct
{
  /*!
   * @brief Pointer to FILE stream which data will be archived to.
   */
  FILE *p_archiveFile;

  /*!
   * @brief String containing the directory to the archive file.
   */
  char *p_archiveDirectory;

  /*!
   * @brief Array containing the data to be archived.
   */
  double variableRow[GARCHIVE_MAX_COLS];

  /*!
   * @brief Array for which names of columns will be stored. These will be the
   *        keys of an ini file.
   */
  char colName[GARCHIVE_MAX_COLS][GARCHIVE_MAX_BUFFER];

  /*!
   * @brief Integer which contains the number of columns to be archived.
   */
  int8_t nCols;

  /*!
   * @brief Integer which contains the index of value loaded to be archived.
   */
  int8_t nVals;
} GArchive;

#ifdef __cplusplus
}
#endif

#endif /* H_GARCHIVE_STRUCT_H */
