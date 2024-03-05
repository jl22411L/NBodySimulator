/*
 *    @File:         GParser_loadFloatArray.c
 *
 *    @ Brief:       Loads an array of floats
 *
 *    @ Date:        23/12/2023
 *
 */

#include <string.h>

/* Function Includes */
#include "GParser/PrivateFunctions/GParser_PrivateFunctions.h"
#include "GParser/PublicFunctions/GParser_PublicFunctions.h"

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
#include "GParser/ConstantDefs/GParser_Const.h"

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GConversions/GConversions.h"
#include "GLog/GLog.h"
#include "GZero/GZero.h"

/*
 *  Refer to respective header file for function description
 */
int GParser_loadFloatArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows)
{
  /* Declaring local variables */
  dictionary *p_dic_tmp;
  char        section_buffer[GCONST_BUFFER_256];
  char        key_inputBuffer[GCONST_BUFFER_256];
  char        key_iniBuffer[GCONST_BUFFER_256];
  char        dataToLoad_buffer[GCONST_BUFFER_1024];
  int16_t     col;
  int16_t     row;
  int16_t     i;
  int16_t     j;
  int16_t     k;

  /* Clearing Buffers */
  GZero(&section_buffer, char[GCONST_BUFFER_1024]);
  GZero(&key_inputBuffer, char[GCONST_BUFFER_256]);
  GZero(&dataToLoad_buffer, char[GCONST_BUFFER_1024]);
  GZero(&key_iniBuffer, char[GCONST_BUFFER_256]);
  p_dic_tmp = NULL;

  /* Defining local variables */
  i = 0;
  j = 0;

  /* Parsing data input for section */
  for (i = 0; *(p_dataFromIni_in + i) != ':'; i++)
  {
    section_buffer[i] = *(p_dataFromIni_in + i);
  }

  /* Parsing data input for key */
  for (i; *(p_dataFromIni_in + i + 1) != '\0'; i++)
  {
    key_inputBuffer[j] = *(p_dataFromIni_in + i + 1);
    j++;
  }

  /* Find dictionary for coresponding section */
  for (i = 0; i < p_GParser_state->maxNumberSection; i++)
  {
    /* load tempory dictionary */
    p_dic_tmp = *(p_dic + i);

    /* check to see if section name matches */
    if (strcmp(p_dic_tmp->section, section_buffer) == 0)
    {
      break;
    }
  }

  /* Check to see if section exists */
  if (i == p_GParser_state->maxNumberSection)
  {
    GError("Section not found: %s", section_buffer);
  }

  /* ---------------------------- LOAD ARRAY ----------------------------- */

  /* Load key for 1D array */
  if (nRows == 1)
  {
    for (i = 0; i < nCols; i++)
    {
      /* Find the name of the key */
      if (sprintf(
              dataToLoad_buffer,
              "%s:%s[%d]",
              section_buffer,
              key_inputBuffer,
              j) < 0)
      {
        GError("Wasn't able to write the key");
      }

      /* Load the key into the memory address */
      GParser_loadFloat(
          p_GParser_state,
          p_dic,
          (p_dataDestination_out + j + i * nCols),
          dataToLoad_buffer);
    }
  }
  /* Load key for 2D array */
  else
  {
    for (i = 0; i < nRows; i++)
    {
      for (j = 0; j < nCols; j++)
      {
        if (sprintf(
                dataToLoad_buffer,
                "%s:%s[%d][%d]",
                section_buffer,
                key_inputBuffer,
                i,
                j) < 0)
        {
          GError("Wasn't able to write the key");
        }

        GParser_loadFloat(
            p_GParser_state,
            p_dic,
            (p_dataDestination_out + j + i * nCols),
            dataToLoad_buffer);
      }
    }
  }

  /* Clear buffer */
  GZero(&key_iniBuffer, char[256]);

  return GCONST_TRUE;
}
