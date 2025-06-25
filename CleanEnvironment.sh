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

# Remove items from Build Environment Folder
if [[ -d BuildEnvironment/CMakeFiles ]]; then
  echo "[MSG] Removing contents within BuildEnvironment..."
  rm -r BuildEnvironment/*
  echo "[...] Contents removed"
else
  echo "[MSG] No contents to remove"
  echo "[...] Aborting"
fi

# Clean branches of git repository
git switch main &&
git pull --prune &&
git branch --format '%(refname:short) %(upstream:track)' | awk '$2 == "[gone]" { print $1 }' | xargs -r git branch -D
