/*
 *   @File:         GParser_PrivateFunctions.h
 *
 *   @ Brief:       Header file containting Private Functions for GParser
 *
 *   @ Description: Contains the definitions of all the private functions for
 *                  GParser library.
 *
 */

#ifndef H_GPARSER_PRIVATE_FUNCTIONS_H
#define H_GPARSER_PRIVATE_FUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/* --------------------------- PRIVATE FUNCTIONS --------------------------- */

/*!
 * @description: Function which cleares the buffers used to load section, keys
 *               and values, along with the indexes and size variables which
 *               are used in loading a scetion into a dictionary.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *              If an error in the codes execution occurs, the function will
 *              return a GCONST_FALSE
 */
extern int GParser_clearBuffers(GParser_State *p_GParser_state);

/*!
 * @description: Function which is run when the state of the parser in loading
 *               a comment. This function effcetively waits for a new line and
 *               ignores other data until then.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_comment(GParser_State *p_GParser_state, const char cursor_in);

/*!
 * @description: This function finds the total number of sections within an ini
 *               file.
 *
 * @param[in]    file
 *               Pointer that contains the data from an ini file.
 *
 * @param[out]   p_maxNumberSection_out
 *               Pointer to where max number of sections value should be stored.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out);

/*!
 * @desctiption: This function loads a dictionary, which contains a section,
 *               along with keys and values. The function will return a pointer
 *               to the heap of memory which contains all the dictionaries for
 *               the different sections.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @return       dictionary
 *               This is a pointer to the heap of memory which contains the
 *               dictionaries.
 */
extern dictionary *GParser_loadDictionary(GParser_State *p_GParser_state);

/*!
 * @description: This function loads the keys. Once the key has been loaded the
 *               state will change so that the parser will wait for the equals.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_loadingKey(GParser_State *p_GParser_state, const char cursor_in);

/*!
 * @description: This function loads the section. Once the section has been
 *               loaded, the state changes to waiting for new line or waiting
 *               for command.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int GParser_loadingSection(
    GParser_State *p_GParser_state,
    const char     cursor_in);

/*!
 * @description: This function is used for loading a string. It works similar
 *               to loadingValue but it waits until " before moving on.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int GParser_loadingStringValue(
    GParser_State *p_GParser_state,
    const char     cursor_in);

/*!
 * @description: This function is laoding a value for a key. Once the value has
 *               been loaded, it will move onto waiting for new line or waiting
 *               for command.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_loadingValue(GParser_State *p_GParser_state, const char cursor_in);

/*!
 * @description: This function waits for the cursor to be an equals sign then
 *               sets the state to wait for value, or loading value.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_waitingEquals(GParser_State *p_GParser_state, const char cursor_in);

/*!
 * @description: This function looks at the cursor and determines what command
 *               to carry out.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int GParser_waitingForCommand(
    GParser_State *p_GParser_state,
    const char     cursor_in);

/*!
 * @description: This function looks at the cursor and checks to see if it is a
 *               '\n'. If so it changes the state to wait for a command.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int GParser_waitingForNewLine(
    GParser_State *p_GParser_state,
    const char     cursor);

/*!
 * @description: This function waits for a value to load. Once the value has
 *               been reached it will change the state to loading value.
 *
 * @param[in]    p_GParser_state
 *               Pointer to GParser State Struct which contains the information
 *               used in the GParser module to load the ini file.
 *
 * @param[in]    cursor_in
 *               cursour which contains the next charecter from the inis file.
 *
 * @return       Upon a successful completion, the fucntion will return a
 *               GCONST_TRUE
 *
 *               If an error in the codes execution occurs, the function will
 *               return a GCONST_FALSE
 */
extern int
    GParser_waitingValue(GParser_State *p_GParser_state, const char cursor);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PRIVATE_FUNCTIONS_H */
