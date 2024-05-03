/*
 *    @File:         Gravity_Const.h
 *
 *    @ Brief:       Defines the constants for Gravity modeul
 *
 *    @ Date:        20/03/2024
 *
 */

#ifndef H_GRAVITY_CONSTANT_H
#define H_GRAVITY_CONSTANT_H

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

/* -------------------------------------------------------------------------- *
 *                              CONSTANT DEFINES                              *
 * -------------------------------------------------------------------------- */

#define UNIVERSAL_GRAVITATIONAL_CONSTANT (6.67430E-11)

/* -------------------------------------------------------------------------- *
 *                             ENUMERATORS DEFINES                            *
 * -------------------------------------------------------------------------- */

/*!
 * @brief       Enumerator used for determining the gravity model to be used
 *              in the simulation. The models incriment in 10's in the
 *              event that in the future variants of the models want to be
 *              implemented.
 */
typedef enum GravityModelEnum
{
  /*!
   * @brief     No Gravity
   *
   * @details   Model which will not include and gravity on the bodies passed.
   *            While this is not representetive of a real system it is worth
   *            having for special simulations, such as testing.
   */
  NoGravityModel = 0,

  /*!
   * @brief     Flat Earth Model
   *
   * @details   Flat Earth model which assumes that the gravity vector is always
   *            pointing in the -Z direction in the fixed frame.
   */
  FlatEarthGravityModel = 10,

  /*!
   *
   * @brief     Dual Body Model
   *
   * @details   Model which finds the gravity only between 2 rigid bodies.
   *            This ideally should be used with a rigid body and some other
   *            body, however in theory it can be with any 2 bodies.
   *
   *            This model takes two rigig bodies, finds the distance between
   *            them in the fixed frame and uses Netwonian laws to find
   *            the gravity force between them.
   *
   *            This is effectively the same as the NBody model but optimised
   *            for 2 bodies.
   */
  DualBodyGravityModel = 20,

  /*!
   * @brief     NBody Model
   *
   * @details   Model used for simulating N rigid bodies. This iterates through
   *            an array of rigid body structs to find body i. For each body it
   *            will then iterate through the array again, skipping out the
   *            current body being assessed (body j). The distance in the fixed
   *            frame will be found between body i and j, using Newtonian laws
   *            to then find the gravity force between the two bodies. This
   *            will repeat for all bodies j, summing the results to find the
   *            resultant gravity force on body i. This will repeat for all
   *            bodies on i.
   *
   *            TODO: There is room for optimisation in this algorithm.
   *                  Find a way to make the algorithm not have to recalculate
   *                  the forces for each body and try resuse calcualtions.
   */
  NBodyGravityModel = 30
} GravityModel;

#ifdef __cplusplus
}
#endif

#endif /* H_GRAVITY_CONSTANT_H */
