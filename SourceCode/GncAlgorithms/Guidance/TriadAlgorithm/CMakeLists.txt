add_library(TriadAlgorithm
  PublicFunctions/TriadAlgorithm_getDcm.c
  PublicFunctions/TriadAlgorithm_getQuat.c
)


target_link_libraries(TriadAlgorithm
  PUBLIC GMath
)
