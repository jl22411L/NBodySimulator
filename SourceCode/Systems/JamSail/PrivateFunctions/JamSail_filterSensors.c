/*
 *    @File:         JamSail_filterSensors.c
 *
 *    @Brief:        Prviate fucntion which contains the definition of the
 *                   function which step JamSail's ADCS.
 *
 *    @Date:         08/04/2025
 *
 */

#include <stdint.h>

/* Function Includes */
/* None */

/* Structure Include */
#include "JamSail/DataStructs/JamSail_ParamsStruct.h"
#include "JamSail/DataStructs/JamSail_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
#include "GConst/GConst.h"
#include "GUtilities/GUtilities.h"

int JamSail_filterSensors(JamSail_State  *p_jamSail_state_out,
                          JamSail_Params *p_jamSail_params_in)
{
  /* Declare local variables */
  uint8_t i;

  /* Apply low pass filter to sensors */
  for (i = 0; i < 3; i++)
  {
    /* Apply low pass filter to Gyro */
    SensorFilter_lowPassFilter(
        (p_jamSail_params_in->gyro_params.lowPassCutoffFrequency_Hz),
        Utilities.simTimeStep_s,
        (p_jamSail_state_out->gyro_state.measuredGyroVector_Sen_rads[i]),
        (p_jamSail_state_out->gyro_state
             .previousFilteredGyroVector_Sen_rads[i]),
        &(p_jamSail_state_out->gyro_state.filteredGyroVector_Sen_rads[i]));

    /* Apply low pass filter to Magnetometer */
    SensorFilter_lowPassFilter(
        (p_jamSail_params_in->magnetometer_params.lowPassCutoffFrequency_Hz),
        Utilities.simTimeStep_s,
        (p_jamSail_state_out->magnetometer_state
             .measuredMagneticField_Sen_nT[i]),
        (p_jamSail_state_out->magnetometer_state
             .previousFilteredMagneticField_Sen_nT[i]),
        &(p_jamSail_state_out->magnetometer_state
              .filteredMagneticField_Sen_nT[i]));

    /* Apply low pass filter to Sun Sensor */
    SensorFilter_lowPassFilter(
        (p_jamSail_params_in->sunSensor_params.lowPassCutoffFrequency_Hz),
        Utilities.simTimeStep_s,
        (p_jamSail_state_out->sunSensor_state.measuredSunVector_Sen_m[i]),
        (p_jamSail_state_out->sunSensor_state
             .previousFilteredSunVector_Sen_m[i]),
        &(p_jamSail_state_out->sunSensor_state.filteredSunVector_Sen_m[i]));
  }

  return GCONST_TRUE;
}