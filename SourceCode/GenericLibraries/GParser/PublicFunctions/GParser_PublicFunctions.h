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

/* Function Includes */
/* None */

/* Structure Include */
#include "GParser/DataStructs/Dictionary.h"
#include "GParser/DataStructs/GParser_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

// TODO
extern int GParser_closeParams(GParser_State *p_GParser_state, dictionary **p_dic);

// TODO
extern int GParser_loadDouble(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    double        *p_dataDestination,
    char          *p_dataFromIni);

// TODO
extern int GParser_loadFloat(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination,
    char          *p_dataFromIni);

// TODO
extern int GParser_loadFloatArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    float         *p_dataDestination,
    char          *p_dataFromIni,
    int            nCols,
    int            nRows);

// TODO
extern int GParser_loadInt_8(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int8_t        *p_dataDestination,
    char          *p_dataFromIni);

// TODO
extern int GParser_loadInt(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination,
    char          *p_dataFromIni);

// TODO
extern int GParser_loadIntArray(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination,
    char          *p_dataFromIni,
    int            nCols,
    int            nRows);

// TODO
extern dictionary **GParser_loadParams(GParser_State *p_GParser_state, const char *filePath);

// TODO
extern int GParser_loadString(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    char         **p_dataDestination,
    char          *p_dataFromIni);

// TODO
extern int GParser_loadUInt(
    GParser_State *p_GParser_state,
    dictionary   **p_dic,
    int           *p_dataDestination,
    char          *p_dataFromIni);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PUBLICFUNCTIONS_H */