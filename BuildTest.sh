#! /bin/bash

#
#    @ File:        BuildTest.sh
#
#    @ Brief:       Builds the code base.
#
#    @ Description: This script builds the code base and the execuatbles.
#                   Currently, it is configured for windows. May need to be
#                   adapted for other operating systems.
#
#    @ Date:        16/12/2023
#

set -e

echo "[MSG] Building Code Base"
echo "[...] Setting Source and Build directories..."

#------------------------- CHECKING PARSED ARGUMENTS -------------------------#

debug_argument=""
for input in $@; do
  case ${input} in
    -d|--debug*)   debug_argument="-DCMAKE_BUILD_TYPE=Debug"
    ;;

    *)        echo "[ERR] Unknown input: ${input}"
              exit 1
  esac
done

#------------------------------- RUNNING CMAKE -------------------------------#

# Find the name of the operating system
operating_system="$(uname -s)"

# Run cmake depending on the system being run on
case "${operating_system}" in
  Linux*)   cmake -S SourceCode -B BuildEnvironment ${debug_argument} -G "Unix Makefiles"
  ;;

  MINGW*)   cmake -S SourceCode -B BuildEnvironment ${debug_argument} -G "MinGW Makefiles"
  ;;

  *)        echo "[ERR] Could not recognize operating system"
            echo "[...] operating_system_argument: ${operating_system_argument}"
            exit 1
esac


echo "[...] # ------------------------------------ BUILDING ----------------------------------- # "

cmake --build BuildEnvironment

echo "[...] # --------------------------------- BUILD COMPLETE -------------------------------- # "

