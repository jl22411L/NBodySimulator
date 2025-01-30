# Set minimum required version of cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(NBodySim)

# Set C compiler
set(CMAKE_C_COMPILER gcc)

# Set C++ compiler
set(CMAKE_CXX_COMPILER g++)

# Set C standard
set(CMAKE_C_STANDARD 90)

# Set Source Directory
set(SRC_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Set relative directories within project
set(BODIES_PATH ${SRC_DIRECTORY}/Bodies)
set(GENERIC_PATH ${SRC_DIRECTORY}/GenericLibraries)
set(GNC_ALGORITHMS_PATH ${SRC_DIRECTORY}/GncAlgorithms)
set(PHYSICS_PATH ${SRC_DIRECTORY}/Physics)
set(SENSOR_PATH ${SRC_DIRECTORY}/Sensors)
set(SYSTEM_PATH ${SRC_DIRECTORY}/Systems)
set(TEST_PATH ${SRC_DIRECTORY}/TestCase)
set(UNITTEST_PATH ${TEST_PATH}/UnitTest)

# Directories to be included in scripts
include_directories(${BODIES_PATH})
include_directories(${GENERIC_PATH})
include_directories(${GNC_ALGORITHMS_PATH})
include_directories(${PHYSICS_PATH})
include_directories(${SENSOR_PATH})
include_directories(${SYSTEM_PATH})
include_directories(${TEST_PATH})
include_directories(${UNITTEST_PATH})

# ----------- Add subdirectories which contain CMakeLists.txt file ---------- #

# Bodies
add_subdirectory(${BODIES_PATH}/BodyMgr)
add_subdirectory(${BODIES_PATH}/CelestialBody)
add_subdirectory(${BODIES_PATH}/RigidBody)
add_subdirectory(${BODIES_PATH}/SatelliteBody)
add_subdirectory(${BODIES_PATH}/UavBody)

# Generic Libraries
add_subdirectory(${GENERIC_PATH}/GArchive)
add_subdirectory(${GENERIC_PATH}/GConversions)
add_subdirectory(${GENERIC_PATH}/GIntegral)
add_subdirectory(${GENERIC_PATH}/GLegPoly)
add_subdirectory(${GENERIC_PATH}/GParser)
add_subdirectory(${GENERIC_PATH}/GMath)
add_subdirectory(${GENERIC_PATH}/GTime)
add_subdirectory(${GENERIC_PATH}/GUtilities)

# GNC Algorithms
add_subdirectory(${GNC_ALGORITHMS_PATH}/Guidance/TriadAlgorithm)

# Physics Modules
add_subdirectory(${PHYSICS_PATH}/Gravity)
add_subdirectory(${PHYSICS_PATH}/Igrf)

# Sensor Modules
add_subdirectory(${SENSOR_PATH}/SunSensor)
add_subdirectory(${SENSOR_PATH}/Magnetometer)

# System Modules
add_subdirectory(${SYSTEM_PATH}/JamSail)

# Test Cases
add_subdirectory(${TEST_PATH}/SystemTest)
add_subdirectory(${TEST_PATH}/JamSailSimulation)

# Unit Tests
add_subdirectory(${UNITTEST_PATH}/GParser_UnitTest)
add_subdirectory(${UNITTEST_PATH}/RigidBodyTest)
add_subdirectory(${UNITTEST_PATH}/ModuleUnitTest)
