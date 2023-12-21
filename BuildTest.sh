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

echo "$1"

echo "[MSG] Building Code Base"
echo "[...] Setting Source and Build directories..."

if [ "$1" == "Debug" ]; then
  echo "[MSG] Building in Debug mode"

  echo "[...] # ------------------------------ SETTING DIRECTORIES ------------------------------ # "
  cmake -S SourceCode -B BuildCode -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
else
  echo "[...] # ----------------------------- SETTING DIRECTORIES ----------------------------- # "

  cmake -S SourceCode -B BuildCode -G "MinGW Makefiles"
fi
echo "[...] # ------------------------------------ BUILDING ----------------------------------- # "

cmake --build BuildCode

echo "[...] # --------------------------------- BUILD COMPLETE -------------------------------- # "



