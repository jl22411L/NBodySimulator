/*
 *    @File:         Igrf_PrivateFunctions.h
 *
 *    @Brief:        Header file containing the private functions for IGRF
 *                   module.
 *
 *    @Date:         21/10/2024
 *
 */

#ifndef H_IGRF_PRIVATEFUNCTIONS_H
#define H_IGRF_PRIVATEFUNCTIONS_H

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
 * @brief         Function which will apply the quasi-schmidt normalisation to
 *                the gaussian coefficients and their linear rate. This is to
 *                reduce the amount of computation required when finding the
 *                magnetic field vector in the loop. This way, only the
 *                associated legendre polynomial needs to be calucalted in the
 *                loop without normalising them at each time step.
 *
 * @param[out]    p_igrf_params_out
 *                Pointer to an Igrf_Params struct which has the gaussian
 *                coefficients and linear rates loaded in.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Igrf_applyNormalisation(Igrf_Params *p_igrf_params_out);

/*!
 * @brief         Function which checks to make sure that the spherical
 *                coordinates of the secondary body in the GeoCent frame are
 *                acceptable for the Igrf model. It checks to make sure that
 *                the colatitude is within an acceptable range and won't cause
 *                any singularities within the model.
 *
 * @param[inout]  p_sphericalSecondaryBodyPosition_GeoCent_m_in
 *                Pointer containing the address of vector representing the
 *                spherical coordiantes of the secondary body in the geocentric
 *                frame of the primary body.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Igrf_checkTolerances(double *p_sphericalSecondaryBodyPosition_GeoCent_m_in);

/*!
 * @brief         This function will take the magnetic field from the NED frame
 *                and convert it into the body frame of the primary body.
 *
 * @param[in]     p_magneticField_Ned_nT_in
 *                Pointer containing the address of magnetic field vector in the
 *                Ned frame.
 *
 * @param[in]     p_sphericalCoofinates_in
 *                Pointer containing the address of vector representing
 *                spherical coordinates of the secondary body.
 *
 *                NOTE: Radial element is not used in function, hence unit tag
 *                      is eliminated from the variable name.
 *
 * @param[out]    p_magneticField_GeoCen_nT_out
 *                Pointer containing the address of magnetic field vector in the
 *                GeoCen frame of the primaty body frame.
 *
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Igrf_convertFromNedToGeoCen(double *p_magneticField_Ned_nT_in,
                                       double *p_sphericalCoofinates_in,
                                       double *p_magneticField_GeoCen_nT_out);

/*!
 * @brief         Function which will find the gausian coefficients for current
 *                time of sim.
 *
 * @param[out]    p_gCoefficients_nT_out
 *                Pointer to an array which the output g-gaussian coefficients
 *                will be stored.
 *
 * @param[out]    p_hCoefficients_nT_out
 *                Pointer to an array which the output h-gaussian coefficients
 *                will be stored.
 *
 * @param[in]     simTime_s_in
 *                Time of the simulation.
 *
 * @param[in]     p_igrf_params_in
 *                Pointer to an Igrf_Params struct which has the params loaded.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Igrf_findCoefficients(double      *p_gCoefficients_nT_out,
                                 double      *p_hCoefficients_nT_out,
                                 double       simTime_s_in,
                                 Igrf_Params *p_igrf_params_in);

/*!
 * @brief         This function finds the magnetic field in NED geocentric frame
 *                of the primary body.
 *
 * @param[out]    p_magneticFieldVector_ned_out
 *                Pointer to vector which the magnetic field will be outputted
 * to.
 *
 * @param[in]     p_secondaryBodyPosSph_geoCent_m_in
 *                Pointer which contains the position of the secondary body in
 *                spherical coordinates. This is in the Geocentric frame of the
 *                primary body.
 *
 * @param[in]     p_associatedLegPoly_in
 *                Pointer to an array containing the outputs of the associated
 *                legendre polynomials.
 *
 * @param[in]     p_assocaitedLegPolyDerivitive_in
 *                Pointer to an array containing the outputs of the associated
 *                legendre polynomials derivitive.
 *
 * @param[in]     primaryBodyRadius_m_in
 *                Radius of the primary body.
 *
 * @param[in]     simTime_s_in
 *                Current time of simulation in UNIX time.
 *
 * @param[in]     p_igrf_params_in
 *                Pointer to Igrf_Params struct.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int
    Igrf_findMagneticFieldInNed(double      *p_magneticFieldVector_ned_out,
                                double      *p_secondaryBodyPosSph_geoCent_m_in,
                                double      *p_associatedLegPoly_in,
                                double      *p_assocaitedLegPolyDerivitive_in,
                                double       primaryBodyRadius_m_in,
                                double       simTime_s_in,
                                Igrf_Params *p_igrf_params_in);

/*!
 * @brief         Function which will take the position of two bodies in the
 *                fixed frame and quaternion representing the rotation of the
 *                body which is producing a magnetic field (the primary body)
 *                and find the cartesian coordinates of the secondary body in
 *                the geocentric frame of the primary body.
 *
 *                NOTE: The primary body here is in reference to the body which
 *                      is producing the magnetic field.
 *
 *                      The secondary body is in reference to the body who will
 *                      experience the magnetic field from the primary body.
 *
 * @param[in]     p_secondryBodyPosition_fix_in
 *                Pointer containing the address of the vector which has the
 *                position of the secondary body in the fixed frame. Should be
 *                in cartesian format.
 *
 * @param[in]     p_primaryBodyPosition_fix_in
 *                Pointer containing the address of the vector which has the
 *                position of the primary body in the fixed frame. Should be
 *                in cartesian format.
 *
 * @param[in]     p_primaryBodyQuat_fixToBod_in
 *                Pointer containing the address of the quaternion which has the
 *                attitude of the primary body (Rotation if from fix frame to
 *                body frame of the primary body).
 *
 * @param[out]    p_secondryBodyCartesianPosition_geoCen_out
 *                Pointer containing the address of the vector which contains
 *                the position of secondary body in the geocentric frame of the
 *                primary body.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Igrf_findPositionInGeocentricBodyFrame(
    double *p_secondryBodyPosition_fix_in,
    double *p_primaryBodyPosition_fix_in,
    double *p_primaryBodyQuat_fixToBod_in,
    double *p_secondryBodyCartesianPosition_geoCen_out);

/*!
 * @brief         Function which loads the gaussian coefficients and linear
 *                rates, for a particular iteration of the IGRF model, into a
 *                Igrf_Params struct.
 *
 * @param[out]    p_igrf_params_out
 *                Pointer to an Igrf_Params struct which will have the gaussian
 *                coefficients and linear rates loaded into.
 *
 * @param[in]     p_paramsFilePath_in
 *                String which containst the filepath to the Igrf.ini params
 *                file.
 *
 * @param[in]     nMaxDegree_in
 *                Integer representing the maximum degree of the IGRF model
 *                which will be laoded.
 *
 * @param[in]     igrfIteration_in
 *                Integer representing the iteration of the IGRF model to be
 *                loaded.
 *
 * @return        Upon a successful completion, the fucntion will return a
 *                GCONST_TRUE. If an error in the codes execution occurs, the
 *                function will return a GCONST_FALSE.
 */
extern int Igrf_loadParams(Igrf_Params *p_igrf_params_out,
                           const char  *p_paramsFilePath_in,
                           uint8_t      nMaxDegree_in,
                           uint8_t      igrfIteration_in);

#ifdef __cplusplus
}
#endif
#endif /* H_IGRF_PRIVATEFUNCTIONS_H */