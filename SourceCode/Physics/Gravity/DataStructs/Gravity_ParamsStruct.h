/*
 *    @File:         Gravity_ParamsStruct.h
 *
 *    @ Brief:       Struct which contains params for the Gravity Module
 *
 *    @ Date:        29/04/2024
 *
 */

#ifndef H_GRAVITY_PARAMSSTRUCT_H
#define H_GRAVITY_PARAMSSTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
/* None */

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct Gravity_ParamsStruct
{
  /*!
   * @details   Integer indicating what gravity model should be used.
   *            (Look at Grvaity Module enumerators for up to date list)
   *
   *            0  - No Gravity
   *            10 - Flat Earth
   *            20 - Dual Gravity Model
   *            30 - N-Body Gravity Model
   *
   * @unit      N/A
   * @frame     N/A
   */
  uint8_t gravityModel;

  /*!
   * @details   Constant which representst the acceleration caused by gravity
   *            at Sea level.
   *
   *            This member is only used in a flat earth model. It is advised
   *            to set it to 0 if any other model is being used.
   */
  double seaLevelGravitationalAcceleration_ms2;

} Gravity_Params;

#ifdef __cplusplus
}
#endif

#endif /* H_GRAVITY_PARAMSSTRUCT_H */
