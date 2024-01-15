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






#------------------------------- SET VARIABLES -------------------------------#

# Flag to indicate if to run test in gdb
DEBUG_FLAG=False

# Variable storing the machines operating system
OPERATING_SYSTEM="$(uname -s)"

#------------------------------- PARSING INPUTS ------------------------------#

# Checks to see if there is an input
if [ "$#" -eq 0 ]; then
  echo "Need to Input Test Case"
  exit 1
fi

POSITIONAL_ARGUMENTS=""
for input in "${@}"; do
  case ${input} in
    -d|--debug)
      debugFlag=True
      ;;
    -*|--*)
      echo "[ERR] Unknown argument ${input}"
      exit 1
      ;;
    *)
      POSITIONAL_ARGUMENTS="${POSITIONAL_ARGUMENTS}/${input}"
      ;;
  esac
done

RELATIVE_PATH_TO_TEST=${POSITIONAL_ARGUMENTS}

#---------------------- FINDING TEST & EXECUTABLE NAME -----------------------#

# Run find executable depending on the operating system
case "${OPERATING_SYSTEM}" in
  Linux*)
    EXECUTABLE_NAME="${input}"
    ;;

  MINGW*)   
    EXECUTABLE_NAME="${input}.exe"
    ;;

  *)        echo "[ERR] Could not recognize operating system"
            echo "[...] operating_system_argument: ${operating_system_argument}"
            exit 1
esac

# Finding name of Test Case
TEST_CASE="${input}"

#----------------------- CREATING & CHECKING DIRECTORIES ---------------------#

# Getting current timestamp
TEST_DATE="`date +%Y_%m_%d_%H_%M_%S`"

# Defining path variables
PATH_TO_ROOT=${PWD}
PATH_TO_TEST_SOURCE_CODE="SourceCode/TestCase${RELATIVE_PATH_TO_TEST}"
PATH_TO_TEST_BUILD_CODE="BuildCode/TestCase${RELATIVE_PATH_TO_TEST}"
PATH_TO_TEST_EXECUTABLE="${PATH_TO_TEST_BUILD_CODE}/${EXECUTABLE_NAME}"
PATH_TO_TEST_RUN="TestRuns${RELATIVE_PATH_TO_TEST}/${TEST_CASE}_${TEST_DATE}"

# Checking path to Source Code exists
if [ ! -d "${PATH_TO_TEST_SOURCE_CODE}" ]; then
  echo "[ERR] Path \"${PATH_TO_TEST_SOURCE_CODE}\" does not exist."
  exit 1
else
  echo "[MSG] Path to test declaration:   ${PATH_TO_TEST_SOURCE_CODE}"
fi

# Checking path to Build Code exists
if [ ! -d "${PATH_TO_TEST_BUILD_CODE}" ]; then
  echo "[ERR] Path \"${PATH_TO_TEST_BUILD_CODE}\" does not exist."
  exit 1
else
  echo "[MSG] Path to executable folder:  ${PATH_TO_TEST_BUILD_CODE}"
fi

# Checking path to executable exists
if [ ! -f "${PATH_TO_TEST_EXECUTABLE}" ]; then
  echo "[ERR] Path \"${PATH_TO_TEST_EXECUTABLE}\" does not exist."
  exit 1
else
  echo "[MSG] Path to executable file:    ${PATH_TO_TEST_EXECUTABLE}"
fi

echo "[INF] Paths checked successfully"

# Creating Test Case folder
echo "[MSG] # -------------------------------- CREATING FILES -------------------------------- #"

mkdir -p ${PATH_TO_TEST_RUN}
echo "[MSG] Created directory: ${PATH_TO_TEST_RUN}"

echo "[INF] Created files correctly"

# Copying Executable
echo "[MSG] # ------------------------------ COPYING EXECUTABLE ------------------------------ #"

cp ${PATH_TO_TEST_EXECUTABLE} ${PATH_TO_TEST_RUN}
chmod 755 ${PATH_TO_TEST_RUN}/${EXECUTABLE_NAME}

echo "[INF] Executable Copies Successfully"

# Copying Parameters
echo "[MSG] # ------------------------------ COPYING PARAMETERS ------------------------------ #"

# Copying Generic Parameters
cp -r Parameters/ModelParameters/* ${PATH_TO_TEST_RUN}/Parameters/
cp -r Parameters/TestParameters/* ${PATH_TO_TEST_RUN}/Parameters/

# Check if Specific parameters exist then copy
if [ -e Parameters/SpecificParameters/${PATH_TO_TEST_RUN}/ModelParameters/*.ini ]; then
  for file in Parameters/SpecificParameters/${PATH_TO_TEST_RUN}/ModelParameters/*.ini; do
    cp ${file} ${PATH_TO_TEST_RUN}/Parameters/
    chmod +775 ${PATH_TO_TEST_RUN}/Parameters/${file}
  done
fi

if [ -e Parameters/SpecificParameters/${PATH_TO_TEST_RUN}/TestParameters/*.ini ]; then
  for file in Parameters/SpecificParameters/${PATH_TO_TEST_RUN}/TestParameters/*.ini; do
    cp ${file} ${PATH_TO_TEST_RUN}/Parameters/
    chmod +775 ${PATH_TO_TEST_RUN}/Parameters/${file} 
  done
fi
echo "[MSG] Specific Test Parameters copied successfully"


echo "[INF] Parameters copied succesfully"

# Running Executable
echo "[MSG] # ------------------------------ RUINNING EXECUTABLE ----------------------------- #"

echo "[...] Running executable: ${PATH_TO_TEST_RUN}/${EXECUTABLE_NAME}"

if [ ${DEBUG_FLAG} == True ]; then
  cd "${PATH_TO_TEST_RUN}"
  echo "[...] Running in Debug Mode"
  gdb ./${EXECUTABLE_NAME}
  cd ${PATH_TO_ROOT}
else 
  cd "${PATH_TO_TEST_RUN}"
  ./${EXECUTABLE_NAME}
  cd ${PATH_TO_ROOT}
fi