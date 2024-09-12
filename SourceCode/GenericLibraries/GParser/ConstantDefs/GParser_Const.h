/*
 *   @File:         GParser_Const.h
 *
 *   @ Brief:       Contains constants for GParser
 *
 *   @ Description: Contains variables requried by GParser
 *
 */

#ifndef H_GPARSER_CONSTANTDEFS_H
#define H_GPARSER_CONSTANTDEFS_H

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

/* ------------------------------------------------------------------------ *
 * BUFFER SIZES
 * ------------------------------------------------------------------------ */
#define GPARSER_SECTION_BUFFERSIZE           (1024)
#define GPARSER_KEY_BUFFERSIZE               (4096)
#define GPARSER_VALUE_BUFFERSIZE             (4096)

/* ------------------------------------------------------------------------ *
 * STATES
 * ------------------------------------------------------------------------ */

// TODO write description of the different states
#define GPARSER_STATE_WAITING_FOR_COMMAND    (0)
#define GPARSER_STATE_WAITING_NEWLINE        (1)
#define GPARSER_STATE_COMMENT                (2)
#define GPARSER_STATE_LOADING_SECTION        (10)
#define GPARSER_STATE_LOADING_KEY            (20)
#define GPARSER_STATE_KEY_WAITING_FOR_EQUALS (21)
#define GPARSER_STATE_WAITING_VALUE          (22)
#define GPARSER_STATE_LOADING_VALUE          (23)
#define GPARSER_STATE_LOADING_STRING_VALUE   (24)
#define GPARSER_STATE_FINISHED               (99)

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_CONSTANTDEFS_H */
