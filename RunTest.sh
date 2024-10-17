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

# TODO: Write a documentation string of how the bash script works and will
#       display when a -h flag is parsed.


#------------------------------- SET VARIABLES -------------------------------#

# Flag to indicate if to run test in gdb
DEBUG_FLAG=False

# Flag to indicate to run test run using valgrind
VALGRIND_FLAG=False

# Variable storing the machines operating system
OPERATING_SYSTEM="$(uname -s)"

# Set Specific Parameters to DefaulParameters
SPECIFIC_PARAMETERS=""

#------------------------------- PARSING INPUTS ------------------------------#

# Checks to see if there is an input
if [ "$#" -eq 0 ]; then
  echo "Need to Input Test Case"
  exit 1
fi

POSITIONAL_ARGUMENTS=""
while [[ $# -gt 0 ]]; do
  # Set next input from command line
  input=${1}

  case ${input} in
    # Flag to run the executable in debug mode using gdb
    -d|--debug)
      DEBUG_FLAG=True
      ;;

    # Flag to indicate to run using Valgrind
    -v|--valgrind)
      VALGRIND_FLAG=True
      ;;

    # Flag to indicate to use a specific parameter set
    -s)
      # Shift arguments by one
      shift

      # Set specific parameters folder
      SPECIFIC_PARAMETERS=${1}
      ;;

    # To indicate that flag is unknown
    -*|--*)
      echo "[ERR] Unknown argument ${input}"
      exit 1
      ;;

    # Positional Arguments
    *)
      POSITIONAL_ARGUMENTS="${POSITIONAL_ARGUMENTS}${input}/"
      ;;
  esac

  # Shift inputs by 1
  shift
done

# Set the relative path to the positinal arguments
RELATIVE_PATH_TO_TEST="${POSITIONAL_ARGUMENTS}"

# --------------------------- PROCESS RELATIVE PATH --------------------------- #

# Remove all trailing /. (Done this way, instead of using %, to cover the event
# user inputs / at the end of the string and hecne the POSITIONAL_ARGUMENTS
# variable ends with //)
while [ "${RELATIVE_PATH_TO_TEST: -1}" == "/" ]; do
  RELATIVE_PATH_TO_TEST="${RELATIVE_PATH_TO_TEST%/}"
done
echo "${RELATIVE_PATH_TO_TEST}"

# Check to make sure the path does not include "SourceCode/TestCase". This is
# done so that if the user wants they can just put the relative path to the
# test run source code, taking advantage of the Tab Autocomplete.
if [[ "${RELATIVE_PATH_TO_TEST:0:20}" == "SourceCode/TestCase/" ]]; then
  RELATIVE_PATH_TO_TEST="${RELATIVE_PATH_TO_TEST:20}"
fi

# Find the executable name based on the final subdirectory. (This follows the
# standard that the executable name will have the same name as the test case)
EXECUTABLE_NAME="${RELATIVE_PATH_TO_TEST##*/}"

# --------------------- FIND TEST DIR & EXECUTABLE NAME ----------------------- #

# Finding name of Test Case
TEST_CASE="${EXECUTABLE_NAME}"

# Run find executable depending on the operating system
case "${OPERATING_SYSTEM}" in
  Linux*)
    EXECUTABLE_NAME="${EXECUTABLE_NAME}"
    ;;

  MINGW*)
    EXECUTABLE_NAME="${EXECUTABLE_NAME}.exe"
    ;;

  *)        echo "[ERR] Could not recognize operating system"
            echo "[...] operating_system_argument: ${operating_system_argument}"
            exit 1
esac

#----------------------- CREATING & CHECKING DIRECTORIES ---------------------#

# Getting current timestamp
TEST_DATE="`date +%Y_%m_%d_%H_%M_%S`"

# Defining path variables
PATH_TO_ROOT=${PWD}
PATH_TO_TEST_EXECUTABLE="BuildCode/TestCase/${RELATIVE_PATH_TO_TEST}/${EXECUTABLE_NAME}"
PATH_TO_TEST_RUN="TestRuns/${RELATIVE_PATH_TO_TEST}${TEST_CASE}_${TEST_DATE}/"

# Checking path to Build Code exists
if [ ! -x "${PATH_TO_TEST_EXECUTABLE}" ]; then
  echo "[ERR] Path \"${PATH_TO_TEST_EXECUTABLE}\" does not exist."
  exit 1
else
  echo "[MSG] Path to executable folder:  ${PATH_TO_TEST_EXECUTABLE}"
fi

# Creating Test Case folder
echo "[MSG] # -------------------------------- CREATING FILES -------------------------------- #"
echo "[...]"

# Creating Parameters Directory
mkdir -p ${PATH_TO_TEST_RUN}/Parameters

# Creating Output Directory
mkdir -p ${PATH_TO_TEST_RUN}/OutputData

# Creating Archive Directory
mkdir -p ${PATH_TO_TEST_RUN}/ArchiveData

# Creating Directory for Bodies
mkdir -p ${PATH_TO_TEST_RUN}/Bodies

# Output message to indiate that archives have been created
echo "[MSG] Created test run: ${PATH_TO_TEST_RUN}"

# Copying Executable
echo "[MSG] # ------------------------------ COPYING EXECUTABLE ------------------------------ #"
echo "[...]"

cp ${PATH_TO_TEST_EXECUTABLE} ${PATH_TO_TEST_RUN}/
echo "[INF] Executable Copied Successfully"

# Copying Parameters
echo "[MSG] # ------------------------------ COPYING PARAMETERS ------------------------------ #"
echo "[...]"

# Copy Default Parameter set for test run
cp -r Parameters/TestParameters/${RELATIVE_PATH_TO_TEST}/DefaultParameters/. ${PATH_TO_TEST_RUN}/Parameters/
echo "[MSG] Default Test Parameters copied successfully"

# If there is a specific parameters, copy the parameters
if [ -n "${SPECIFIC_PARAMETERS}" ]; then
  cp -r Parameters/TestParameters/${RELATIVE_PATH_TO_TEST}/${SPECIFIC_PARAMETERS}/. ${PATH_TO_TEST_RUN}/Parameters/
fi
echo "[INF] Parameters copied succesfully"

# Running Executable
echo "[MSG] # ------------------------------ RUINNING EXECUTABLE ----------------------------- #"
echo "[...]"
echo "[MSG] Running executable: ${PATH_TO_TEST_RUN}${EXECUTABLE_NAME}"

if [ ${DEBUG_FLAG} == True ]; then
  cd "${PATH_TO_TEST_RUN}"
  echo "[...] Running in Debug Mode"
  echo ""
  gdb ./${EXECUTABLE_NAME}
  echo ""
  cd ${PATH_TO_ROOT}
elif [ ${VALGRIND_FLAG} == True ]; then
  cd "${PATH_TO_TEST_RUN}"
  echo "[...] Running in Debug Mode"
  echo ""
  valgrind --leak-check=full ./${EXECUTABLE_NAME}
  echo ""
  cd ${PATH_TO_ROOT}
else
  cd "${PATH_TO_TEST_RUN}"
  echo ""
  ./${EXECUTABLE_NAME}
  echo ""
  cd ${PATH_TO_ROOT}
fi

echo "[MSG] # --------------------------------- TEST COMPLETE -------------------------------- #"
