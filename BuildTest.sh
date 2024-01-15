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

for input in $@; do
  case ${input} in
    -d|--debug*)   additional_arguments="${additional_arguments} -DCMAKE_BUILD_TYPE=Debug"
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
  Linux*)   cmake -S SourceCode -B BuildCode -G "Unix Makefiles" ${additional_arguments}
  ;;

  MINGW*)   cmake -G "MinGW Makefiles" ${additional_arguments}
  ;;

  *)        echo "[ERR] Could not recognize operating system"
            echo "[...] operating_system_argument: ${operating_system_argument}"
            exit 1
esac


echo "[...] # ------------------------------------ BUILDING ----------------------------------- # "

cmake --build BuildCode

echo "[...] # --------------------------------- BUILD COMPLETE -------------------------------- # "

