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

#include <stdio.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Function will initialise an archive. Takes the name of the
 *                data that is being archived and also a pointer to a FILE
 *                pointer which to sotre that file in. The directory is then
 *                created and a csv file is open to write in. The file should
 *                then be closed at the end of a simulation.
 *
 *                Note: Archived data should be streamed out at every time step.
 *                This is different to outputData which is archived when the
 *                sensor is meant to output data.
 *
 * @param[in]     p_archiveDataFilename_in
 *                String containting path to which the data will be archived.
 *                (e.g ArchiveData/RigidBody)
 *
 * @param[out]    p_archiveFilePath_out
 *                Pointer to a csv file which the data will be written to.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE
 *
 *                If an error in the codes execution occurs, the function will
 *                return a GCONST_FALSE
 */
extern int GArchive_init(
    const char *p_archiveDataFilename_in,
    FILE       *p_archiveDataFile_out);

#ifdef __cplusplus
}
#endif

#endif /* H_GARCHIVE_PUBLICFUNCTIONS_H */