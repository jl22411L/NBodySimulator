add_library(SensorFilters
  PublicFunctions/SensorFilter_lowPassFilter.c
)

set(LIB_LIST

)

target_link_libraries(SensorFilters ${LIB_LIST})