# Set minimum required version of cmake
cmake_minimum_required(VERSION 3.5)

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
set(GENERIC_PATH ${SRC_DIRECTORY}/GenericLibraries)
set(BODIES_PATH ${SRC_DIRECTORY}/Bodies)
set(MODULES_PATH ${SRC_DIRECTORY}/Modules)
set(TEST_PATH ${SRC_DIRECTORY}/TestCase)
set(UNITTEST_PATH ${SRC_DIRECTORY}/TestCase/UnitTest)

# Directories to be included in scripts
include_directories(${GENERIC_PATH})
include_directories(${BODIES_PATH})
include_directories(${MODULES_PATH})
include_directories(${TEST_PATH})
include_directories(${UNITTEST_PATH})

# include_directories(/SourceCode/GenericLibraries)

# ---- Add subdirectories which contain CMakeLists.txt file ---- #

# Generic Libraries
add_subdirectory(${GENERIC_PATH}/GParser)
add_subdirectory(${GENERIC_PATH}/GConversions)
add_subdirectory(${GENERIC_PATH}/GUtilities)

# Bodies
add_subdirectory(${BODIES_PATH}/RigidBody)

# Modules

# Test Cases
# None 

# Unit Tests
add_subdirectory(${UNITTEST_PATH}/GParser_UnitTest)
add_subdirectory(${UNITTEST_PATH}/RigidBodyTest)
