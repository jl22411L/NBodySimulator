/*
 *    @File:         BodyMgr_BodyTypeEnum.h
 *
 *    @Brief:        File which contains the enumerator for the different body
 *                   types.
 *
 *    @Date:         29/05/2024
 *
 */

#ifndef H_BODYMGR_BODYTYPEENUM_H
#define H_BODYMGR_BODYTYPEENUM_H

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

typedef enum BodyMgr_BodyTypeEnum
{
  /*!
   * @details   Constant to indicate that the body type is of a rigid body type.
   *            This should only be used for special purposes.
   */
  RIGID_BODY = 0,

  /*!
   * @details   Constant to indicate that the body type is of a celestial body
   *            type. This should primarely be used for planets and moons.
   */
  CELESTIAL_BODY = 1,

  /*!
   * @details   Constant to indicate that the body type is of a satellite body
   *            type. This should primarely be used for satellites.
   */
  SATELLITE_BODY = 2,

  /*!
   * @details   Constant to indicate that the body type is of a UAV body
   *            type. This should primarely be used for UAV's.
   */
  UAV_BODY = 3
} BodyMgr_BodyType;

#ifdef __cplusplus
}
#endif
#endif /* H_BODYMGR_BODYTYPEENUM_H */
