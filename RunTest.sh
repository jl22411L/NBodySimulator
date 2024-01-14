#! /bin/bash

#
#    @ File:        RunTest.sh
#
#    @ Brief:       This script runs a test
#
#    @ Description: This script creates a timestamped folder in TestRuns which
#                   will have the executable and necessary parameters cp into
#                   it. Parameters in specific parameters will overwrite the
#                   general parameters.
#
#    @ Date:        16/12/2023
#

set -e

# Checks to see if there is an input
if [ "$#" -eq 0 ]; then
  echo "Need to Input Test Case"
  exit 1
fi

echo "[...]"
echo "[MSG] # -------------------------------- CHECKING PATHS -------------------------------- #"
echo "[...]"

# Flags
debugFlag="False"

# Cycles through the inputs to make path to test and include any features
for i in $@; do
  # Check if Debug is enabled
  echo ${i}
  if [ ${i} = "Debug" ]; then
    debugFlag="True"
    shift 1
  else
    relativePathToTest+="/${i}"
  fi
done
echo $debugFlag
echo "[MSG] Input path:                 ${relativePathToTest}"

# Setting test name
testName="${i}"

# Set variable to executable name
executableName="${testName}.exe"

# Getting current timestamp
testDate="`date +%Y_%m_%d_%H_%M_%S`"

# Defining path variables
pathToRoot=${PWD}
pathToTest_sourceCode="SourceCode/TestCase${relativePathToTest}"
pathToTest_buildCode="BuildCode/TestCase${relativePathToTest}"
pathToTest_executable="${pathToTest_buildCode}/${executableName}"
pathToTest_testCase="TestRuns${relativePathToTest}/${testName}_${testDate}"

# Checking path to Source Code exists
if [ ! -d "${pathToTest_sourceCode}" ]; then
  echo "[ERR] Path \"${pathToTest_sourceCode}\" does not exist."
  exit 1
else
  echo "[MSG] Path to test declaration:   ${pathToTest_sourceCode}"
fi

# Checking path to Build Code exists
if [ ! -d "${pathToTest_buildCode}" ]; then
  echo "[ERR] Path \"${pathToTest_buildCode}\" does not exist."
  exit 1
else
  echo "[MSG] Path to executable folder:  ${pathToTest_buildCode}"
fi

# Checking path to executable exists
if [ ! -f "${pathToTest_executable}" ]; then
  echo "[ERR] Path \"${pathToTest_executable}\" does not exist."
  exit 1
else
  echo "[MSG] Path to executable file:    ${pathToTest_executable}"
fi

echo "[INF] Paths checked successfully"

# Creating Test Case folder
echo "[...]"
echo "[MSG] # -------------------------------- CREATING FILES -------------------------------- #"
echo "[...]"

mkdir -p ${pathToTest_testCase}
echo "[MSG] Created directory: ${pathToTest_testCase}"

echo "[INF] Created files correctly"

# Copying Executable
echo "[...]"
echo "[MSG] # ------------------------------ COPYING EXECUTABLE ------------------------------ #"
echo "[...]"
cp ${pathToTest_executable} ${pathToTest_testCase}

echo "[INF] Executable Copies Successfully"

# Copying Parameters
echo "[...]"
echo "[MSG] # ------------------------------ COPYING PARAMETERS ------------------------------ #"
echo "[...]"

# Copying Generic Parameters
cp -r Parameters/GenericParameters/ModelParameters/. ${pathToTest_testCase}/Parameters/
cp -r Parameters/GenericParameters/TestParameters/. ${pathToTest_testCase}/Parameters/

# Check if Specific parameters exist then copy
if [ -e Parameters/SpecificParameters/${relativePathToTest}/ModelParameters/*.ini ]; then
  for file in Parameters/SpecificParameters/${relativePathToTest}/ModelParameters/*.ini; do
    cp ${file} ${pathToTest_testCase}/Parameters/
  done
fi

if [ -e Parameters/SpecificParameters/${relativePathToTest}/TestParameters/*.ini ]; then
  for file in Parameters/SpecificParameters/${relativePathToTest}/TestParameters/*.ini; do
    cp ${file} ${pathToTest_testCase}/Parameters/
  done
fi
echo "[MSG] Specific Test Parameters copied successfully"


echo "[INF] Parameters copied succesfully"

# Running Executable
echo "[...]"
echo "[MSG] # ------------------------------ RUINNING EXECUTABLE ----------------------------- #"
echo "[...]"

echo "[...] Running executable: ${pathToTest_testCase}/${executableName}"

if [ ${debugFlag} == "True" ]; then
  cd ${pathToTest_testCase}
  echo "[...] Running in Debug Mode"
  gdb ./${executableName}
  cd ${pathToRoot}
else
  cd ${pathToTest_testCase}
  ./${executableName}
  cd ${pathToRoot}
fi