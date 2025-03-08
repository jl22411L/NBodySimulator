add_library(JamSail
  PrivateFunctions/JamSail_attitudeDetermination.c
  PrivateFunctions/JamSail_attitudeEstimation.c
  PublicFunctions/JamSail_init.c
  PublicFunctions/JamSail_step.c
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
)

target_link_libraries(JamSail ${LIB_LIST})