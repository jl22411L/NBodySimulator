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

# Flag to indicate to run test run using valgrind
VALGRIND_FLAG=False

# Variable storing the machines operating system
OPERATING_SYSTEM="$(uname -s)"

# Set Specific Parameters to DefaulParameters
SPECIFIC_PARAMETERS="DefaultParameters"

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
    # FLag to run the executable in debug mode using gdb
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
PATH_TO_TEST_EXECUTABLE="BuildCode/TestCase/${RELATIVE_PATH_TO_TEST}${EXECUTABLE_NAME}"
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

# Copying Generic Parameters
cp -r Parameters/BodyParameters/. ${PATH_TO_TEST_RUN}/Parameters/
cp -r Parameters/ModelParameters/. ${PATH_TO_TEST_RUN}/Parameters/
cp -r Parameters/TestParameters/. ${PATH_TO_TEST_RUN}/Parameters/

# Copy Specific Parameters Set
cp -r Parameters/SpecificParameters/${RELATIVE_PATH_TO_TEST}${SPECIFIC_PARAMETERS}/. ${PATH_TO_TEST_RUN}/Parameters/
echo "[MSG] Specific Test Parameters copied successfully"

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
