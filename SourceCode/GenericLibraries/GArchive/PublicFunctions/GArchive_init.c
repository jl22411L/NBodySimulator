/*
 *    @File:         GArchive_init.c
 *
 *    @ Brief:       Initialises the
 *
 *    @ Description:
 *
 *    @ Date:
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int GArchive_init(
    const char *p_archiveDataFilename_in,
    FILE       *p_archiveDataFile_out)
{
  /* Create directory to archive folder */
  mkdir(p_archiveDataFilename_in, 0775);

  /* Concat the string with path to csv file */
  strncat(p_archiveDataFilename_in, "/Data.csv", 5);

  /* Open the file which the data will be archived in */
  p_archiveDataFile_out = fopen(p_archiveDataFilename_in, "w");

  return GCONST_TRUE;
}