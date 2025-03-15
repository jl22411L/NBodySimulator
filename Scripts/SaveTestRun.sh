#! /bin/bash

#
#    @ File:        RunTest.sh
#
#    @ Brief:       This script includes the function for saving a test run
#
#    @ Date:        15/03/2025
#

function SaveTestRun() {
  echo "[...]"
  echo "[MSG] Name the test run to save it. Leave blank to not save test run."
  read -p "[...] Input: "  userInput
  echo "[...]"

  # Extract test run directory
  TEST_RUN_DIR=${1}

  # Extract test run name
  TEST_RUN_NAME=${2}

  # Extract root directory
  PATH_TO_ROOT=${3}

  # Change to root directory
  cd ${PATH_TO_ROOT}

  # Create directory to saved test runs
  SAVED_TEST_RUN_FOLDER_DIR="${PATH_TO_ROOT}/TestRunsSaved"

  # Reading input and removing files, do nothing, or exit with error
  if [ ${userInput} == "" ]; then
    # Test run has no name. hence do nothing
    exit 0;
  else
    # Create directory to asved test run
    cp -r ${1} ${SAVED_TEST_RUN_FOLDER_DIR}
    mv "${SAVED_TEST_RUN_FOLDER_DIR}/${TEST_RUN_NAME}" "${SAVED_TEST_RUN_FOLDER_DIR}/${TEST_RUN_NAME}_${userInput}"
    echo "[MSG] Test run saved to: ${SAVED_TEST_RUN_FOLDER_DIR}/${TEST_RUN_NAME}_${userInput}"
  fi
}
