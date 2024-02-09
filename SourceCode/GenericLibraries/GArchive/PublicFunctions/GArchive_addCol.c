/*
 *    @File:         GArchive_addCol.c
 *
 *    @ Brief:       Adds a column to the archive config file
 *
 *    @ Date:        06/02/2024
 *
 */

#include <stdint.h>
#include <string.h>

/* Function Includes */
#include "GArchive/PrivateFunctions/GArchive_PrivateFunctions.h"

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
#include "GArchive/ConstantDefs/GArchive_Constants.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GArchive_addCol(
    GArchive   *p_archive_inout,
    const char *p_colName_in,
    uint8_t     nColsAdd_in,
    uint8_t     nRowsAdd_in)
{
  /* Declaring local variables */
  int8_t columnIndex;

  /* Check to make sure inputs are valid */
  if (nColsAdd_in < 1 || nRowsAdd_in < 1)
  {
    GError(
        "Inputs are not valid to add column."
        "nColsAdd_in = %d, nRowsAdd_in = %d",
        nColsAdd_in,
        nRowsAdd_in);
  }

  switch (nColsAdd_in)
  {
  case (1):
    /* Find column which archive is up to */
    columnIndex = p_archive_inout->nCols;

    /* Add the column name to the struct archive */
    strcpy(&p_archive_inout->colName[columnIndex][0], p_colName_in);

    /* Incriment the number of columns */
    p_archive_inout->nCols++;

    break;

  default:
    GArchive_addColArray(
        p_archive_inout,
        p_colName_in,
        nColsAdd_in,
        nRowsAdd_in);
  }

  return GCONST_TRUE;
}
