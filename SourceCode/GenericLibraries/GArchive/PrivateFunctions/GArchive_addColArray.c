/*
 *    @File:         GArchive_addColArray.c
 *
 *    @ Brief:       Adds columns to GArchive struct for an array
 *
 *    @ Date:        06/02/2024
 *
 */

#include <stdint.h>
#include <stdlib.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
#include "GArchive/ConstantDefs/GArchive_Constants.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"


int GArchive_addColArray(
    GArchive   *p_archive_inout,
    const char *p_colName_in,
    uint8_t     nColsAdd_in,
    uint8_t     nRowsAdd_in)
{
  /* Declaring local variables */
  char    buffer[GARCHIVE_MAX_BUFFER];
  int8_t  columnIndex;
  int32_t i;
  int32_t j;

  /* Clear Buffer */
  GZero(buffer, char[GARCHIVE_MAX_BUFFER]);

  /* Check to make sure inputs are valid */
  if (nColsAdd_in < 1 || nRowsAdd_in < 1)
  {
    GError(
        "Inputs are not valid to add column."
        "nColsAdd_in = %d, nRowsAdd_in = %d",
        nColsAdd_in,
        nRowsAdd_in);
  }

  switch (nRowsAdd_in)
  {
  /* Case for 1D vectors */
  case (1):
    /* Iterate for number of columns */
    for (i = 0; i < nColsAdd_in; i++)
    {
      /* Find column which archive is up to */
      columnIndex = p_archive_inout->nCols;

      /* Add the index into the column name */
      sprintf(buffer, "%s[%d]", p_colName_in, i);

      /* Add the column name to archive struct */
      strcpy(&p_archive_inout->colName[columnIndex][0], buffer);

      /* Incriment the number of columns */
      p_archive_inout->nCols++;
    }

    break;
  /* Case for 2D vectors */
  default:
    /* Iterate for number of columns */
    for (i = 0; i < nRowsAdd_in; i++)
    {
      for (j = 0; j < nColsAdd_in; j++)
      {
        /* Find column which archive is up to */
        columnIndex = p_archive_inout->nCols;

        /* Add the index into the column name */
        sprintf(buffer, "%s[%d][%d]", p_colName_in, i, j);

        /* Add the column name to archive struct */
        strcpy(&p_archive_inout->colName[columnIndex][0], buffer);

        /* Incriment the number of columns */
        p_archive_inout->nCols++;
      }
    }
  }

  return GCONST_TRUE;
}