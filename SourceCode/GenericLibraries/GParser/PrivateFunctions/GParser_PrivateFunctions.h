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

extern int GParser_clearBuffers(GParser_State *p_stateStruct);

extern int GParser_comment(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int GParser_findIndex(int *col, int *row, char *key, int startPosition);

extern int GParser_findNumberOfSections(FILE *file, uint8_t *p_maxNumberSection_out);

extern dictionary *GParser_loadDictionary(GParser_State *p_stateStruct);

extern int GParser_loadingKey(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int
    GParser_loadingSection(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int
    GParser_loadingStringValue(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int GParser_loadingValue(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int GParser_waitingEquals(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int
    GParser_waitingForCommand(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int
    GParser_waitingForNewLine(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

extern int GParser_waitingValue(uint8_t *p_state, GParser_State *p_stateStruct, const char cursor);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PRIVATE_FUNCTIONS_H */
