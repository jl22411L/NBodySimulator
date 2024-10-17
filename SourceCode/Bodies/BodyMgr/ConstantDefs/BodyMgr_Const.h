/*
 *    @File:         BodyMgr_Const.h
 *
 *    @Brief:        Header file that conatins constants for BodyMgr
 *
 *    @Date:         29/05/2024
 *
 */

#ifndef H_BODYMGR_CONST_H
#define H_BODYMGR_CONST_H

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
 * @brief       Integer which represents the max number of bodies that can be
 *              loaded into a simulation.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define BODYMGR_MAX_NUMBER_OF_BODIES (256)

/*!
 * @brief      Integer which represents the maximum length of the name of a
 *             body.
 *
 * @frame      N/A
 * @unit       N/A
 */
#define BODYMGR_BODY_NAME_MAX_BUFFER (256)

/*!
 * @brief       Integer which represents the maximum size of the buffer used to
 *              load the parameters for a body.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define BODYMGR_MAX_BUFFER_LENGTH    (256)

#ifdef __cplusplus
}
#endif
#endif /* H_BODYMGR_CONST_H */
