/*
 *   @File:         GParser_PublicFunctions.h
 *
 *   @ Brief:       Contains the Public functions to GParser Library
 *
 */

#ifndef H_GPARSER_PUBLICFUNCTIONS_h
#define H_GPARSER_PUBLICFUNCTIONS_h

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
extern int GParser_loadDouble(
    double      *p_dataDestination,
    char        *p_dataFromIni,
    dictionary **p_dic);

// TODO
extern int GParser_loadFloat(
    float       *p_dataDestination,
    char        *p_dataFromIni,
    dictionary **p_dic);

// TODO
extern int GParser_loadInt(
    int         *p_dataDestination,
    char        *p_dataFromIni,
    dictionary **p_dic);

// TODO
extern dictionary **GParser_loadParams(const char *filePath);

// TODO
extern int GParser_loadString(
    char       **p_dataDestination,
    char        *p_dataFromIni,
    dictionary **p_dic);

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_PUBLICFUNCTIONS_h */