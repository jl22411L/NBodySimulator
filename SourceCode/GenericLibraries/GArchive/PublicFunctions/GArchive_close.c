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
#include "GZero/GZero.h"
#include "GLog/GLog.h"

int GArchive_close(GArchive *p_archive_in)
{
  /* Declare local variables */
  char    buffer[GARCHIVE_MAX_BUFFER];
  FILE   *p_configFile;
  uint8_t i;

  /* Clear buffer */
  GZero(buffer, char[GARCHIVE_MAX_BUFFER]);
  p_configFile = NULL;

  /* Close the file of the data */
  fclose(p_archive_in->p_archiveFolder);

  /* Create string to metadata file */
  sprintf(buffer, "%s/Config.ini", p_archive_in->p_archiveDataFilename);

  /* Open meta data ini file */
  p_configFile = fopen(buffer, "w");

  /* Check to make sure file open correctly */
  if(p_configFile == NULL)
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
    fprintf(p_configFile, "col[%d] = %s \n", i, p_archive_in->colName[i - 1]);
  }

  /* Add new line to bottom of file */
  fprintf(p_configFile, "\n");

  /* Close config file */
  fclose(p_configFile);

  /* Free memory from heap */
  free(p_archive_in->p_archiveDataFilename);

  /* Clear archive */
  GZero(p_archive_in, GArchive);

  return GCONST_TRUE;
}
