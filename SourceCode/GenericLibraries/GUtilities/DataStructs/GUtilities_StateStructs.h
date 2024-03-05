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

} GUtilities;

extern GUtilities Utilities;

#ifdef __cplusplus
}
#endif

#endif /* H_UTILITIES_STATESTRUCT_H */
