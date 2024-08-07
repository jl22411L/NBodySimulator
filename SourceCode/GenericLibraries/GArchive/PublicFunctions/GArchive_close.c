/*
 *    @File:         GArchive_close.c
 *
 *    @ Brief:       Closes the archive and closes the open file
 *
 *    @ Date:
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
#include "GZero/GZero.h"

int GArchive_close(GArchive *p_archive_in)
{
  /* Declare local variables */
  char    confidFileDirectory[GARCHIVE_MAX_BUFFER];
  FILE   *p_configFile;
  uint8_t i;

  /* Clear buffer */
  GZero(confidFileDirectory, char[GARCHIVE_MAX_BUFFER]);
  p_configFile = NULL;

  /* Close the file of the data */
  fclose(p_archive_in->p_archiveFile);

  /* Set archive file pointer to NULL */
  p_archive_in->p_archiveFile = NULL;

  /* Create string to metadata file */
  sprintf(
      confidFileDirectory,
      "%s/Config.ini",
      p_archive_in->p_archiveDirectory);

  /* Open meta data ini file */
  p_configFile = fopen(confidFileDirectory, "w");

  /* Check to make sure file opened correctly */
  if (p_configFile == NULL)
  {
    GError("%s did not open correctly", confidFileDirectory);
  }

  /* Check to make sure file open correctly */
  if (p_configFile == NULL)
  {
    GError("File did not open correctly");
  }

  /* Write Section Name */
  fprintf(p_configFile, "[Config]\n");

  /* Write the simTime member to config file */
  fprintf(p_configFile, "col[0] = simTime_s\n");

  /* Write keys of ini file */
  for (i = 1; i < p_archive_in->nCols + 1; i++)
  {
    /* Write key and value to config file */
    fprintf(p_configFile, "col[%d] = %s\n", i, p_archive_in->colName[i - 1]);
  }

  /* Add new line to bottom of file */
  fprintf(p_configFile, "\n");

  /* Close config file */
  fclose(p_configFile);

  /* Clear archive directory pointer */
  GZero(p_archive_in->p_archiveDirectory, char[GARCHIVE_MAX_BUFFER]);

  /* Clear archive */
  GZero(p_archive_in, GArchive);

  return GCONST_TRUE;
}
