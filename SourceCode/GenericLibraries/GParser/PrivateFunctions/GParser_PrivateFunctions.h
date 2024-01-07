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

// TODO
extern int GParser_clearBuffers(GParser_State *p_GParser_state);

// TODO
extern int GParser_comment(
    GParser_State *p_GParser_state,
    uint8_t       *p_state,
    const char     cursor);

// TODO
extern int GParser_findIndex(
    GParser_State *p_GParser_state,
    int           *col_out,
    int           *row_out,
    char          *key,
    int            startPosition);

// TODO
extern int
    GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out);

// TODO
extern dictionary *GParser_loadDictionary(GParser_State *p_GParser_state);

// TODO
extern int
    GParser_loadingKey(GParser_State *p_GParser_state, const char cursor);

// TODO
extern int
    GParser_loadingSection(GParser_State *p_GParser_state, const char cursor);

// TODO
extern int GParser_loadingStringValue(
    GParser_State *p_GParser_state,
    const char     cursor);

// TODO
extern int
    GParser_loadingValue(GParser_State *p_GParser_state, const char cursor);

// TODO
extern int
    GParser_waitingEquals(GParser_State *p_GParser_state, const char cursor);

// TODO
extern int GParser_waitingForCommand(
    GParser_State *p_GParser_state,
    const char     cursor);

// TODO
extern int GParser_waitingForNewLine(
    GParser_State *p_GParser_state,
    const char     cursor);

// TODO
extern int
    GParser_waitingValue(GParser_State *p_GParser_state, const char cursor);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PRIVATE_FUNCTIONS_H */
