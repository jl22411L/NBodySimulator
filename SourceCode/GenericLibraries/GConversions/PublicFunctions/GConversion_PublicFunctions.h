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

/*!
 * @brief           Function which converts a string to a double
 *
 * @param[out]      p_dataDestination_out
 *                  Pointer to the variable which data will be outputted
 *
 * @param[in]       p_dataSource_in
 *                  Pointer to string which containing value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GConversion_string2double(
    double *p_dataDestination_out,
    char  **p_dataSource_in);

/*!
 * @brief           Function which converts a string to a float
 *
 * @param[out]      p_dataDestination_out
 *                  Pointer to the variable which data will be outputted
 *
 * @param[in]       p_dataSource_in
 *                  Pointer to string which containing value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GConversion_string2float(
    float *p_dataDestination_out,
    char **p_dataSource_in);

/*!
 * @brief           Function which converts a string to a int8
 *
 * @param[out]      p_dataDestination_out
 *                  Pointer to the variable which data will be outputted
 *
 * @param[in]       p_dataSource_in
 *                  Pointer to string which containing value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int GConversion_string2int8(
    int8_t *p_dataDestination_out,
    char  **p_dataSource_in);

/*!
 * @brief           Function which converts a string to an int
 *
 * @param[out]      p_dataDestination_out
 *                  Pointer to the variable which data will be outputted
 *
 * @param[in]       p_dataSource_in
 *                  Pointer to string which containing value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int
    GConversion_string2int(int *p_dataDestination_out, char **p_dataSource_in);

/*!
 * @brief           Function which converts a string to a unsigned int
 *
 * @param[out]      p_dataDestination_out
 *                  Pointer to the variable which data will be outputted
 *
 * @param[in]       p_dataSource_in
 *                  Pointer to string which containing value
 *
 * @return          Upon a successful completion, the fucntion will return a
 *                  GCONST_TRUE. If an error in the codes execution occurs, the
 *                  function will return a GCONST_FALSE
 */
extern int
    GConversion_string2uint(int *p_dataDestination_out, char **p_dataSource_in);

#ifdef __cplusplus
}
#endif

#endif /* H_GCONVERSION_PUBLICFUNCTIONS_H */
