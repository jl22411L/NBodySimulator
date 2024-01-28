/*
 *    @File:         GArchive_PublicFunctions.h
 *
 *    @ Brief:       Header file which contains the public functions for
 *                   GArchive
 *
 *    @ Date:        28/01/2024
 *
 */

#ifndef H_GARCHIVE_PUBLICFUNCTIONS_H
#define H_GARCHIVE_PUBLICFUNCTIONS_H

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
 * @details   Function which initiates the GArchive module. This creates the
 *            directories within the Test Run directory.
 *
 * @return    Upon a successful completion, the fucntion will return a
 *            GCONST_TRUE
 *
 *            If an error in the codes execution occurs, the function will
 *            return a GCONST_FALSE
 */
extern int GArchive_init();

extern int GArchive_double();

#ifdef __cplusplus
}
#endif

#endif /* H_GARCHIVE_PUBLICFUNCTIONS_H */