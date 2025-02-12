/*
 *    @File:         GArchive_writeLine.c
 *
 *    @ Brief:       Write the values in the archive stuct to the archive file.
 *
 *    @ Date:        07/02/2024
 *
 */

#include <stdint.h>
#include <stdio.h>
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
#include "GUtilities/GUtilities.h"
#include "GZero/GZero.h"

int GArchive_writeLine(GArchive *p_archive_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Check to make sure the right number of values have been written */
  if (p_archive_in->nVals != p_archive_in->nCols)
  {
    GError("The number of vals does not match with the number of columns "
           "(nVals=%d, nCols=%d)",
           p_archive_in->nVals,
           p_archive_in->nCols);
  }

  /* Write the timestamp for the data row */
  fprintf(p_archive_in->p_archiveFile, "%lf", Utilities.simTime_s);

  /* Write the data from the columns into the file */
  for (i = 0; i < p_archive_in->nVals; i++)
  {
    fprintf(p_archive_in->p_archiveFile, ",%lf", p_archive_in->variableRow[i]);
  }

  /* Move onto new line */
  fprintf(p_archive_in->p_archiveFile, "\n");

  /* Reset members of struct in preperation for new data to write */
  p_archive_in->nVals = 0;
  GZero(p_archive_in->variableRow, double[GARCHIVE_MAX_COLS]);

  return GCONST_TRUE;
}