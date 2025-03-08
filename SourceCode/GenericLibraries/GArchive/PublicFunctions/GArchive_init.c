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
#include "GLog/GLog.h"
#include "GZero/GZero.h"

int GArchive_init(GArchive *p_archive_in, char *p_archiveDataFilename_in)
{
  /* Declaring local variables */
  char directoryBuffer[GARCHIVE_DIRECTORY_BUFFER];
  char dataFileDirectory[GARCHIVE_DATA_FILE_BUFFER];
  int  i;

  /* Clearing Variables */
  GZero(p_archive_in, GArchive);
  GZero(&directoryBuffer[0], char[GARCHIVE_DIRECTORY_BUFFER]);
  GZero(&dataFileDirectory[0], char[GARCHIVE_DATA_FILE_BUFFER]);

  /* Cycle through file name and make directories recursively */
  for (i = 0; GCONST_TRUE; i++)
  {
    /* Check to see if folder needs to be created */
    if (*(p_archiveDataFilename_in + i) == '/')
    {
      /* Create directory with necessary permissions */
      mkdir(directoryBuffer, 0775);
    }

    /* Add value to directoryBuffer */
    directoryBuffer[i] = *(p_archiveDataFilename_in + i);

    /* If there reached end of string, break the for loop */
    if (*(p_archiveDataFilename_in + i) == '\0')
    {
      mkdir(directoryBuffer, 0775);
      break;
    }
  }

  /* Check input directory does not end with '/' and if so remove it */
  if (directoryBuffer[i - 1] == '/')
  {
    directoryBuffer[i - 1] = '\0';
    i--;
  }

  /* Store directory to archive folder */
  strcpy(p_archive_in->p_archiveDirectory, directoryBuffer);

  /* Create directory to data file */
  sprintf(dataFileDirectory, "%s/Data.csv", directoryBuffer);

  /* Check file exists */
  if (GArchive_checkFileExists(dataFileDirectory) == GCONST_TRUE)
  {
    GWarn("File '%s' already exists", dataFileDirectory);
  }

  /* Open file which to archive data */
  p_archive_in->p_archiveFile = fopen(dataFileDirectory, "w");

  /* Check to make sure file opened correctly */
  if (p_archive_in->p_archiveFile == NULL)
  {
    GError("%s was not able to open", dataFileDirectory);
  }

  /* Clear colum names */
  GZero(p_archive_in->colName,
        char[GARCHIVE_MAX_COLS][GARCHIVE_MAX_COL_NAME_BUFFER]);

  /* Set number of columns to 0 */
  p_archive_in->nCols = 0;

  return GCONST_TRUE;
}
