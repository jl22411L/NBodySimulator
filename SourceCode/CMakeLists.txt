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

# Set Root Directory
set(ROOT_DIRECTORY C:/Users/jason/Desktop/Projects/NBodySimulator)
set(SRC_DIRECTORY ${ROOT_DIRECTORY}/SourceCode)


# Set relative directories within project
set(GENERIC_PATH ${SRC_DIRECTORY}/GenericLibraries)
set(MODULES_PATH ${SRC_DIRECTORY}/Modules)
set(TEST_PATH ${SRC_DIRECTORY}/TestCase)
set(UNITTEST_PATH ${SRC_DIRECTORY}/TestCase/UnitTest)

# Directories to be included in scripts
include_directories(${MODULES_PATH})
include_directories(${GENERIC_PATH})
include_directories(${TEST_PATH})
include_directories(${UNITTEST_PATH})

# include_directories(/SourceCode/GenericLibraries)

# ---- Add subdirectories which contain CMakeLists.txt file ---- #

# Generic Libraries
add_subdirectory(${GENERIC_PATH}/GParser)
add_subdirectory(${GENERIC_PATH}/GConversions)

# Modules

# Test Cases
add_subdirectory(${SRC_DIRECTORY}/TestCase/SimTest)

# Unit Tests
add_subdirectory(${SRC_DIRECTORY}/TestCase/UnitTest/GParser_UnitTest)
