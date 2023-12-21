#! /bin/bash

#
#    @ File:        ClearTestRuns.sh
#
#    @ Brief:       This cleares the TestRuns folder. 
#
#    @ Description: This is to help keep things organised and clean. It will 
#                   prompt the user to confirm if they should be removed. Once
#                   deleted it can't be undone.
#
#    @ Date:        16/12/2023
#

set -e

# Promt the user to confirm they want to remove the test cases
echo "[MSG] Are you sure you want to remove all the folders in TestRuns?...(y/n)"
read -p "[...] Input: "  userInput

# Reading input and removing files, do nothing, or exit with error
if [ ${userInput} == "y" ]; then
  # Checking files in test run
  if [ -f TestRuns/* ] || [ -d TestRuns/* ]; then
    echo "[MSG] Removing folders in TestRuns"
    rm -r TestRuns/*
    echo "[...] Files removed. Clear complete"
    exit 0
  else
    echo "[...] No files to remove."
    echo "[...] Aborting..."
    exit 0
  fi
elif [ ${userInput} == "n" ]; then
  echo "[MSG] Operation aborted"
  exit 0
else
  echo "[ERR] Input not valid"
  exit 1
fi