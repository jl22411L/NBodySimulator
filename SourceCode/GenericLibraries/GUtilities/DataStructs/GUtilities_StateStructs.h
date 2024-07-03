/*
 *    @File:    GUtilities_StateStruct.h
 *
 *    @ Brief:  Contains the definition of the GUtilities struct
 *
 *    @ Date:   05/03/2024
 *
 */

#ifndef H_UTILITIES_STATESTRUCT_H
#define H_UTILITIES_STATESTRUCT_H

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

typedef struct GUtilities_struct
{
  /* ------------------------------------------------------------------------ *
   *                          SIMULATION TIME MEMBERS                         *
   * ------------------------------------------------------------------------ */

  /*!
   * @details   Time of simulation
   *
   * @unit      Seconds
   * @frame     N/A
   */
  double simTime_s;

  /*!
   * @details   TIme step of simulation
   *
   * @unit      Seconds
   * @frame     N/A
   */
  double simTimeStep_s;

  /*!
   * @details   Duration of simulation
   *
   * @unit      Seconds
   * @frame     N/A
   */
  double simTimeDuration_s;

  /*!
   * @details   Integer used to indicate the status of the simulation. If
   *            integer is GCONST_TRUE then the simulation is running. If it is
   *            GCONST_FALSE then the simulation is said to be finished and
   *            hence will complete the current step befor ending the programe.
   *
   * @unit      N/A
   * @frame     N/A
   */
  int8_t runSimStatus;

} GUtilities;

extern GUtilities Utilities;

#ifdef __cplusplus
}
#endif

#endif /* H_UTILITIES_STATESTRUCT_H */
