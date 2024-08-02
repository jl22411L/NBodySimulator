/*
 *    @File:         JamSail_StateStruct.h
 *
 *    @Brief:        Header file containing state struct for JamSail
 *
 *    @Date:         08/07/2024
 *
 */

#ifndef H_JAMESAIL_STATESTRUCT_H
#define H_JAMESAIL_STATESTRUCT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "SatelliteBody/DataStructs/SatelliteBody_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

typedef struct JamSail_StateStruct
{
  /* ######################################################################## *
   *                             SATELLITE MEMBERS                            *
   * ######################################################################## */

  /* None */

  /* ######################################################################## *
   *                            SIMULATION MEMBERS                            *
   * ######################################################################## */

  /*!
   * @details   This member contains the state of JamSail. It is primarely used
   *            for the simulation of the dynamics of the body, and keeping
   *            track of sensor readings.
   */
  SatelliteBody_State satelliteBody_state;

} JamSailState;

#ifdef __cplusplus
}
#endif

#endif /* H_JAMESAIL_STATESTRUCT_H */
