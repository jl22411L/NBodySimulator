/*
 *   @File:         GParser_PublicFunctions.h
 *
 *   @ Brief:       Contains the Public functions to GParser Library
 *
 */

#ifndef H_GPARSER_PUBLICFUNCTIONS_H
#define H_GPARSER_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "GParser/GParser.h"

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @details         This function runs throught the dictionary and sets all the
 *                  memory to 0, before freeing the pointer.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int
    GParser_closeParams(GParser_State *p_GParser_state, dictionary **p_dic);

/*!
 * @details         Function which will load a double into a data destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadDouble(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    double        *p_dataDestination_out,
    char          *p_dataFromIni_in);

/*!
 * @details         Function which will load a double array into a data
 * destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadDoubleArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    double        *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows);

/*!
 * @details         Function which will load a float into a data destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadFloat(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination_out,
    char          *p_dataFromIni_in);

/*!
 * @description:    This function will load a 2D array of any size from an ini
 *                  file.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to a GParser state struct for the ini parser
 *
 * @param[in]       p_dic
 *                  Dictioanry with the sections loaded form the ini parser
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer containig the address of the array to load the data
 *                  into.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @param[in]       nCols_in
 *                  Number of columns in the array to load
 *
 * @param[in]       nRows_in
 *                  Number of rows in the array to load
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function
 *                  will return a GCONST_FALSE
 */
extern int GParser_loadFloatArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows);

/*!
 * @details         Function which will load a int8 into a data destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadInt8(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int8_t        *p_dataDestination_out,
    char          *p_dataFromIni_in);

/*!
 * @details         Function which will load a int into a data destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadInt(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination,
    char          *p_dataFromIni);

/*!
 * @description:    This function will load a 2D array of any size from an ini
 *                  file.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to a GParser state struct for the ini parser
 *
 * @param[in]       p_dic
 *                  Dictioanry with the sections loaded form the ini parser
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer containig the address of the array to load the data
 *                  into.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @param[in]       nCols_in
 *                  Number of columns in the array to load
 *
 * @param[in]       nRows_in
 *                  Number of rows in the array to load
 *
 * @return           Upon a successful completion, the fucntion will return a
 *                   GCONST_TRUE
 *
 *                   If an error in the codes execution occurs, the function
 *                   will return a GCONST_FALSE
 */
extern int GParser_loadIntArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination_out,
    char          *p_dataFromIni_in,
    int            nCols,
    int            nRows);

/*!
 * @description:    This function will load the data from an ini file into a
 *                  dictionary which will be returned to the user. The input
 *                  is the file path to the ini file.
 *
 * @param[in]       filePath
 *                  String to the ini file containting the parameters.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to the state struct for the ini parser
 *
 * @return          dictionary
 *                  Address of an array of dictionaries. Effecitvely each
 *                  dictionary contains the data for a section in the ini
 *                  file. An ini file can have an number of sections.
 *
 *                  The returned address is to access the array outside
 *                  the function to be used when laoding parameters.
 */
extern dictionary **
    GParser_loadParams(GParser_State *p_GParser_state, const char *filePath);

/*!
 * @details         Function which will load a string into a data destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadString(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    char         **p_dataDestination_out,
    char          *p_dataFromIni_in);

/*!
 * @details         Function which will load a unsigned integer into a data
 *                  destionation.
 *
 * @param[in]       p_GParser_state
 *                  Pointer to state struct for GParser module
 *
 * @param[in]       p_dic
 *                  Pointer to dictionary with sections laoded
 *
 * @param[in]       p_dataDestination_out
 *                  Pointer with the address to store the data in from the ini
 *                  file.
 *
 * @param[in]       p_dataFromIni_in
 *                  String which contains the name of the section and key for
 *                  which to load the data from. The format of the string should
 *                  be:
 *
 *                  <SETION>:<KEY>
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE
 *
 *                  If an error in the codes execution occurs, the function will
 *                  return a GCONST_FALSE
 */
extern int GParser_loadUInt(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination_out,
    char          *p_dataFromIni_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PUBLICFUNCTIONS_H */