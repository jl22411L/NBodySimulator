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
   * SATELLITE MEMBERS
   * ######################################################################## */

  /* None */

  /* TODO: The intention here is to have the different models such as IMU and
   *       sun sensors here.
   */

  /* ######################################################################## *
   * SIMULATION MEMBERS
   * ######################################################################## */

  /*!
   * @details   This member contains the address to the satellite body struct
   *            for JamSail.
   */
  SatelliteBody_State *p_satelliteBody_state;

} JamSail_State;

#ifdef __cplusplus
}
#endif

#endif /* H_JAMESAIL_STATESTRUCT_H */
