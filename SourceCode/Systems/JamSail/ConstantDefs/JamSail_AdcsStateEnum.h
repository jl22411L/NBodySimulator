/*!
 *    @File:         JamSail_AdcsStateEnum.h
 *
 *    @Brief:        Header file which contais enumerator for JamSail state
 *                   machine.
 *
 *    @Date:         06/04/2025
 *
 */

#ifndef H_JAMSAIL_STATEENUM_H
#define H_JAMSAIL_STATEENUM_H

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

typedef enum JamSail_AdcsStateEnum
{
  /*!
   * @brief     State of JamSail when the angular velocities are too high
   *            and hence, JamSail needs to detumble.
   */
  DETUMBLING,

  /*!
   * @brief     State of JamSail when nominal operations are being performed.
   */
  NOMINAL,
} JamSail_AdcsState;

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_STATEENUM_H */