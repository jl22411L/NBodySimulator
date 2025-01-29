/*!
 *    @File:         SunSensor_checkWithinFov.c
 *
 *    @Brief:        Function which checks that the sun sensor reading is within
 *                   the fov of the sensor.
 *
 *    @Date:         29/01/2025
 *
 */

#include <math.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "SunSensor/DataStructs/SunSensor_ParamsStruct.h"
#include "SunSensor/DataStructs/SunSensor_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"

int SunSensor_checkWithinFov(SunSensor_State  *p_sunSensor_state_inout,
                             SunSensor_Params *p_sunSensor_params_in)
{
  /* Declare local variables */
  double sunVectorAngle_rad;

  /*!
   * Find the angle between the sun vector and the x axis of the sun sensor.
   *
   * This uses the definition of the dot product to find the angle. The reason
   * the angle is jsut acos of the x position of the sun vector is due to the
   * x axis having the vector [1, 0, 0] and the magnitude of both vectors being
   * one. (If confused do the math and simplify and you shall get this result)
   */
  sunVectorAngle_rad = acos(p_sunSensor_state_inout->trueSunVector_Sensor_m[0]);

  /* Check if vector is outside FOV of sensor */
  if (sunVectorAngle_rad >= p_sunSensor_params_in->sensorFov_rad)
  {
    /* If so, set invalid reading flag to GCONST_TRUE */
    p_sunSensor_state_inout->isSensorReadingInvalid = GCONST_TRUE;
  }

  return GCONST_TRUE;
}