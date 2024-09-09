/*
 *    @File:         GArchive_writeHeader.c
 *
 *    @Brief:        Writes the header for archives
 *
 *    @Date:         08/09/2024
 *
 */

#include <stdint.h>
#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GArchive/GArchive.h"
#include "GConst/GConst.h"

int GArchive_writeHeader(GArchive *p_archive_in)
{
  /* Defining local variables */
  int16_t i;

  /* Add sim time */
  fprintf(p_archive_in->p_archiveFile, "simTime_s");

  /* Write the header for the different columns */
  for (i = 0; i < p_archive_in->nCols; i++)
  {
    fprintf(p_archive_in->p_archiveFile, ",%s", p_archive_in->colName[i]);
  }

  /* Write new line */
  fprintf(p_archive_in->p_archiveFile, "\n");

  return GCONST_TRUE;
}
