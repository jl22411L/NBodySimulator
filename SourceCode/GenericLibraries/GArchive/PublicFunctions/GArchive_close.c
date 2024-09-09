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

  /* Close the file of the data */
  fclose(p_archive_in->p_archiveFile);

  /* Clear archive */
  GZero(p_archive_in, GArchive);

  return GCONST_TRUE;
}
