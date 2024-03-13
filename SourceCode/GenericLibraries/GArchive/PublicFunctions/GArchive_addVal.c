/*
 *    @File:         GArchive_addVal.c
 *
 *    @ Brief:       Adds a value to the value array which will be written.
 *
 *    @ Date:        07/02/2024
 *
 */

#include <stdint.h>

/* Function Includes */
#include "GArchive/PrivateFunctions/GArchive_PrivateFunctions.h"

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
#include "GArchive/ConstantDefs/GArchive_Constants.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GLog/GLog.h"

int GArchive_addVal(GArchive *p_archive_in, double archiveValue_in)
{
  /*
   * Check to make sure that the number of values does not exceed the number of
   * columns.
   */
  if (p_archive_in->nVals >= p_archive_in->nCols)
  {
    GError(
        "You can't have more values than the number of columns (valIndex=%d, "
        "nCols=%d)",
        p_archive_in->nVals,
        p_archive_in->nCols);
  }

  /* Store value in array */
  p_archive_in->variableRow[p_archive_in->nVals] = archiveValue_in;

  /* Incriment the index */
  p_archive_in->nVals++;

  return GCONST_TRUE;
}
