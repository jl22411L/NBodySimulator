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
    dictionary    *p_dic,
    float         *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows)
{
  /* Declaring local variables */
  char    dataToLoad_buffer[GCONST_BUFFER_1024];
  int     dictionaryNumber;
  int16_t col;
  int16_t row;
  int16_t i;
  int16_t j;
  int16_t k;

  /* Clearing Buffers */
  GZero(&dataToLoad_buffer, char[GCONST_BUFFER_1024]);

  /* ---------------------------- LOAD ARRAY ----------------------------- */

  /* Load key for 1D array */
  if (nRows == 1)
  {
    for (i = 0; i < nCols; i++)
    {
      /* Find the name of the key */
      if (sprintf(dataToLoad_buffer, "%s[%d]", p_dataFromIni_in, j) < 0)
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
        if (sprintf(dataToLoad_buffer, "%s[%d][%d]", p_dataFromIni_in, i, j) <
            0)
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

  return GCONST_TRUE;
}
