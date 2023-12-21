#! /bin/bash

#
#    @ File:        CleanEnvironment.sh
# 
#    @ Brief:       Cleares up the code environment
# 
#    @ Description: This scrip is used to clean up the environment, primarly
#                   by cleaning the BuildCode file. This is meant to help
#                   make sure that the project can be built from a clean
#                   state and isn't relying on cach data.
#
#    @ Date:        16/12/2023
#

set -e

if [ -f BuildCode/* ] || [-d BuildCode/* ]; then
  echo "[MSG] Removing contents within BuildCode..."
  rm -r BuildCode/*
  echo "[...] Contents removed"
else
  echo "[MSG] No contents to remove"
  echo "[...] Aborting"
fi
