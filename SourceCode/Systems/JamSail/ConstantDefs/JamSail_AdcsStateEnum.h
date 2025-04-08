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
   * @brief     State of JamSail when it is at start up. This state should only
   *            be set when JamSail is turned on for the first time or
   *            restarted.
   */

  JAMSAIL_ADCSSTATE_STARTUP = 0,

  /*!
   * @brief     State of JamSail when the angular velocities are too high
   *            and hence, JamSail needs to detumble.
   */
  JAMSAIL_ADCSSTATE_DETUMBLING = 1,

  /*!
   * @brief     State of JamSail when nominal operations are being performed.
   */
  JAMSAIL_ADCSSTATE_NOMINAL = 2,
} JamSail_AdcsState;

#ifdef __cplusplus
}
#endif
#endif /* H_JAMSAIL_STATEENUM_H */