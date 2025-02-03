/*
 *    @File:         Igrf_PublicFunctions.h
 *
 *    @Brief:        Contains the public functions for the Igrf library
 *
 *    @Date:         11/09/2024
 *
 */

#ifndef H_IGRF_PUBLICFUNCTIONS_H
#define H_IGRF_PUBLICFUNCTIONS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Function Includes */
/* None */

/* Structure Include */
#include "Igrf/DataStructs/Igrf_ParamsStruct.h"

/* Data include */
/* None */

/* Generic Libraries */
/* None */

/*!
 * @brief       Function which will load the IGRF model from the params .ini
 *              file. This will load the parameter to find the epoch data and
 *              the linear rates. The struct which is inputted into the function
 *              will be loaded with the coefficients for the epoch time also
 *              specified in the parameter file.
 *
 * @param[out]   p_igrf_params_out
 *              Pointer containing the adress of an IGRF params struct. This
 *              struct will have its params loaded into.
 *
 * @param[in]   p_paramsFilePath_in
 *              Pointer to a string containing the name of .ini file which
 *              contains the parameters for the IGRF model.
 *
 * @return      GCONST_TRUE is returned upon the successful completion of the
 *              function. GCONST_FALSE is returned to indicate that an error has
 *              occured which prohibits the software from going further.
 */
extern int Igrf_init(Igrf_Params *p_igrf_params_out,
                     const char  *p_paramsFilePath_in,
                     uint8_t      nMaxDegree_in,
                     uint8_t      igrfIteration_in);

/*!
 * @brief       Function which finds the magnetic field in Ned frame of primary
 *              body.
 *
 * @param[in]   p_igrf_params_in
 *              Pointer to Igrf_Params struct with parameters loaded.
 *
 * @param[in]   p_sphericalCoordinates_GeoCen_m_in
 *              Pointer containing the addres of spherical coordinates of the
 *              point in the geo centri frame which the magnetic field will be
 *              modelled. Note, the function will find the co latitude from the
 *              latitude will not change the value in the inputted vector.
 *
 * @param[in]   primaryBodyRadius_m_in
 *              Radius of primary body producing the magnetic field.
 *
 * @param[in]   simTime_s_in
 *              Time of simulation in unix format. If not using unix time, set
 *              to 0.
 *
 * @param[out]  p_magneticFieldVector_Ned_nT_out
 *              Pointer to vector which magnetic field in North-East-Down frame
 *              will be outputted.
 *
 * @return      GCONST_TRUE is returned upon the successful completion of the
 *              function. GCONST_FALSE is returned to indicate that an error has
 *              occured which prohibits the software from going further.
 */
extern int Igrf_step(Igrf_Params *p_igrf_params_in,
                     double      *p_sphericalCoordinates_GeoCen_m_in,
                     double       primaryBodyRadius_m_in,
                     double       simTime_s_in,
                     double      *p_magneticFieldVector_Ned_nT_out);

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PUBLICFUNCTIONS_H */
