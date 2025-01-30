/*!
 *    @File:         Magnetometer_PublicFunctions.h
 *
 *    @Brief:        Header file which contains the public functions of the
 *                   magnetometer sensor.
 *
 *    @Date:         30/01/2025
 *
 */

#ifndef H_MAGNETOMETER_PUBLICFUNCTIONS_H
#define H_MAGNETOMETER_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Magnetometer/DataStructs/Magnetometer_ParamsStruct.h"
#include "Magnetometer/DataStructs/Magnetometer_StateStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief         Function which will initialize the magnetometer model. Will
 *                archive the body to the approprate body that is passed
 *                through. If no body is provided, sensor will be archived to
 *                generic archive folders in test run.
 *
 * @param[in]     p_magnetometerParamFilename_in
 *                String containing the filename of the parameters ini file.
 *                These parameters will be loaded into the Magnetometer.
 *
 * @param[in]     p_magnetometerParams_out
 *                Pointer containing the address for the state struct of the sun
 *                sensor.
 *
 * @param[in]     p_magnetometerState_out
 *                Pointer containing address of the params struct for the sun
 *                sensor.
 *
 * @param[in]     p_sensorBody_in
 *                String for the body which the sensor belongs to. This is so
 *                the sensor can archived with the appropriate body.
 *
 *                Note: If the sensor does not belong to a body, passing an
 *                empty string as an input "", will cause the archive to be
 *                initialised in the root Archive directory.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Magnetometer_init(const char *p_magnetometerParamFilename_in,
                             Magnetometer_Params *p_magnetometerParams_out,
                             Magnetometer_State  *p_magnetometerState_out,
                             const char          *p_sensorBody_in);

#ifdef __cplusplus
}
#endif
#endif /* H_MAGNETOMETER_PUBLICFUNCTIONS_H */