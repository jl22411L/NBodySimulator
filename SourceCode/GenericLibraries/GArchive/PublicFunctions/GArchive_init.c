/*
 *    @File:         GArchive_init.c
 *
 *    @ Brief:       Initialises the archive struct
 *
 *    @ Date:        07/02/2024
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GArchive/DataStructs/GArchive_Struct.h"

/* Data include */
#include "GArchive/ConstantDefs/GArchive_Constants.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GZero/GZero.h"

int GArchive_init(GArchive *p_archive_in, char *p_archiveDataFilename_in)
{
  /* Declaring local variables */
  char buffer[GARCHIVE_MAX_BUFFER];
  int  i;

  /* Clearing Variables */
  GZero(&buffer, char[GARCHIVE_MAX_BUFFER]);
  GZero(p_archive_in, GArchive);

  /* Cycle through file name and make directories recursively */
  for (i = 0; GCONST_TRUE; i++)
  {
    /* Check to see if folder needs to be created */
    if (*(p_archiveDataFilename_in + i) == '/' ||
        *(p_archiveDataFilename_in + i) == '\0')
    {
      /* Create directory with necessary permissions */
      mkdir(buffer, 0775);
    }

    /* Add next charecter of file path to buffer */
    buffer[i] = *(p_archiveDataFilename_in + i);

    /* If reached end of string break for loop */
    if (*(p_archiveDataFilename_in + i) == '\0')
    {
      /* If last charecter in string is '/', remove */
      if (buffer[i - 1] == '/')
      {
        buffer[i - 1] = '\0';
      }
      break;
    }
  }

  /* Find length of buffer */
  i = strlen(buffer);

  /* Assign memory for the filename */
  p_archive_in->p_archiveDataFilename = (char *)calloc(i, sizeof(char));

  /* Store directory to archive folder */
  strcpy(p_archive_in->p_archiveDataFilename, buffer);

  /* Create file path to data config file */
  strncat(buffer, "/Data.csv", 9);

  /* Open file which to archive data */
  p_archive_in->p_archiveFolder = fopen(buffer, "w");

  /* Clear colum names */
  GZero(p_archive_in->colName, char[GARCHIVE_MAX_COLS][GARCHIVE_MAX_BUFFER]);

  /* Set number of columns to 0 */
  p_archive_in->nCols = 0;

  return GCONST_TRUE;
}