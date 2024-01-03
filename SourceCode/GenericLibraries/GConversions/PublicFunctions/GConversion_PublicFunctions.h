/*
 *   @File:         GConversions_PublicFunctions.h
 *
 *   @ Brief:       Containts definitions of public functions for GConversions
 *
 *   @ Time:        23/12/2023
 *
 */

#ifndef H_GCONVERSION_PUBLICFUNCTIONS_H
#define H_GCONVERSION_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

// TODO
extern int GConversion_string2double(double *p_dataDestination, char **p_dataSource);

// TODO
extern int GConversion_string2float(float *p_dataDestination, char **p_dataSource);

// TODO
extern int GConversion_string2int_8(int8_t *p_dataDestination, char **p_dataSource);

// TODO
extern int GConversion_string2int(int *p_dataDestination, char **p_dataSource);

extern int GConversion_string2uint(int *p_dataDestination, char **p_dataSource);

#ifdef __cplusplus
}
#endif

#endif /* H_GCONVERSION_PUBLICFUNCTIONS_H */
