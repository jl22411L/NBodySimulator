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

/*!
 * @brief       Constant used for declaring memory to the buffer which will
 *              contain the section name when a section is being loaded.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_SECTION_BUFFERSIZE                    (1024)

/*!
 * @brief       Constant used for declaring memory to the buffer which will
 *              contain the section name when a key from a section is being
 *              loaded from an ini file.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_KEY_BUFFERSIZE                        (4096)

/*!
 * @brief       Constant used for declaring memory to the buffer which will
 *              contain the section name when a value from a section is being
 *              loaded from an ini file.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_VALUE_BUFFERSIZE                      (4096)

/*!
 * @brief       Constant used for assigning memory on the stack to a buffer
 *              which holds the section when an array is being loaded from an
 *              ini file.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_LOAD_ARRAY_SECTION_BUFFER             (256)

/*!
 * @brief       Constant used for assigning memory on the stack to a buffer
 *              which holds the keys when an array is being loaded from an ini
 *              file.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_LOAD_ARRAY_KEY_INPUT_BUFFER           (256)

/*!
 * @brief       Constant used for assigning memory on the stack to a buffer
 *              which holds the keys when an array is being loaded from an ini
 *              file.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_LOAD_ARRAY_DATA_TO_LOAD_BUFFER        (256)

/* ------------------------------------------------------------------------ *
 * DICTIONARY CONSTANTS
 * ------------------------------------------------------------------------ */

/*!
 * @brief       Constant to indicate the maximum number of keys a dictionary can
 *              hold, along with the maximum number of its corresponding pair.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_DICTIONARY_MAX_KEY_VALUE_PAIRS_NUMBER (128)

/*!
 * @brief       Constant which is used to indicate the maximum length a key can
 *              be.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_DICTIONARY_MAX_KEY_LENGTH             (64)

/*!
 * @brief       Constant which is used to indicate the maximum length a value
 *              can be.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_DICTIONARY_MAX_VALUE_LENGTH           (64)

/* ------------------------------------------------------------------------ *
 * STATES
 * ------------------------------------------------------------------------ */

// TODO: Change states to an enum

/*!
 * @brief       State which is used to indacte that the parser is waiting for a
 *              command.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_WAITING_FOR_COMMAND             (0)

/*!
 * @brief       State to indicate that the parser is waiting for a new line.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_WAITING_NEWLINE                 (1)

/*!
 * @brief       State to indicate that the parser is currently reading a
 *              comment. This differs from waiting to a new line as that will
 *              throw errors if text is encountered. This just waits for a '\n'.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_COMMENT                         (2)

/*!
 * @brief       State to indicate that the parser is loading a section.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_LOADING_SECTION                 (10)

/*!
 * @brief       State to indicate that the parser is loading a key.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_LOADING_KEY                     (20)

/*!
 * @brief       State to indicate that the parser is waiting for an equals. It
 *              will throw an error unless the charecter it is reading is a '\t'
 *              or a space, in which it will do nothing. Once an equals is
 *              reached, the state gets updated. (Follow function to get an up
 *              to date finding of what the state is being updated to)
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_KEY_WAITING_FOR_EQUALS          (21)

/*!
 * @brief       State to indicate that the parser is waiting for a value.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_WAITING_VALUE                   (22)

/*!
 * @brief       State to indicate that a value is being loaded into the parser.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_LOADING_VALUE                   (23)

/*!
 * @brief       State to indicate that a string is being loaded, and hence is
 *              less restrictive on what is considered an invalud charecter.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_LOADING_STRING_VALUE            (24)

/*!
 * @brief       State to indicate that the parser has finished parsing the ini
 *              file and break the while loop.
 *
 * @frame       N/A
 * @unit        N/A
 */
#define GPARSER_STATE_FINISHED                        (99)

#ifdef __cplusplus
}
#endif

#endif /* H_GPARSER_CONSTANTDEFS_H */
