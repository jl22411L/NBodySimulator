add_library(JamSail
  PrivateFunctions/JamSail_archiveData.c
  PrivateFunctions/JamSail_attitudeDetermination.c
  PrivateFunctions/JamSail_attitudeEstimation.c
  PrivateFunctions/JamSail_controlAlgorithm.c
  PrivateFunctions/JamSail_detumblingAlgorithm.c
  PrivateFunctions/JamSail_estimationEkfLoadStateVector.c
  PrivateFunctions/JamSail_fillObservationJacobian.c
  PrivateFunctions/JamSail_fillStateJacobian.c
  PrivateFunctions/JamSail_filterSensors.c
  PrivateFunctions/JamSail_findRequiredQuaternion.c
  PrivateFunctions/JamSail_findStateDerivitive.c
  PrivateFunctions/JamSail_initAttitudeDetermination.c
  PrivateFunctions/JamSail_nominalAlgorithm.c
  PrivateFunctions/JamSail_sunSearchingControl.c
  PrivateFunctions/JamSail_sunTrackingControl.c
  PrivateFunctions/JamSail_updateEstimateMembers.c
  PrivateFunctions/JamSail_updateState.c
  PublicFunctions/JamSail_init.c
  PublicFunctions/JamSail_step.c
  PublicFunctions/JamSail_terminate.c
)

set(LIB_LIST
  PRIVATE BodyMgr
  PRIVATE CelestialBody
  PRIVATE SatelliteBody
  PRIVATE SunSensor
  PRIVATE Magnetometer
  PRIVATE Gyro
  PRIVATE Magnetorquer
  PRIVATE GParser
  PRIVATE GMath
  PRIVATE ContinuousEkf
  PRIVATE GRand
  PRIVATE SensorFilters
  PRIVATE TriadAlgorithm
  PRIVATE KeplarianPropogation
)

target_link_libraries(JamSail ${LIB_LIST})