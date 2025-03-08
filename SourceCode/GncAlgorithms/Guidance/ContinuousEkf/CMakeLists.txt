add_library(ContinuousEkf
  PrivateFunctions/ContinuousEkf_findErrorCovarianceDerivitive.c
  PrivateFunctions/ContinuousEkf_findKalmanGain.c
  PrivateFunctions/ContinuousEkf_findUpdatedErrorCovariance.c
  PrivateFunctions/ContinuousEkf_stateCorrection.c
  PrivateFunctions/ContinuousEkf_stepCovariance.c
  PublicFunctions/ContinuousEkf_step.c
)

target_link_libraries(ContinuousEkf
  PRIVATE GMath
)