#! /bin/bash

#
#    @ File:        SetUpDevelopmentEnvironment.sh
#
#    @ Brief:       Sets up the environment for the simulator repository
#
#    @ Description: This script's purpose is to set up the githooks and
#                   initiate any settings that need to be set for the
#                   simulator. It effectively should be run once by a user
#                   which allows their system to be set up without much hassel.
#
#    @ Date:        30/12/23
#

set -e

#---------------------------- SETTING UP GITHOOKS ----------------------------#

#
# This will copy all the Git Hooks, found in ".Configuration/GitHooks"
#

echo "[MSG] Setting up githooks"
echo "[...]..."

# Check to make sure files are in git hooks directory
if [ -d .git/hooks ]; then
  echo "[MSG] Clearing git hooks"
  echo "[...]"
  rm -r .git/hooks
fi

# Make directory for githooks
mkdir .git/hooks

# Move hooks
echo "[MSG] Copying hooks:"
cp -v .Configuration/GitHooks/* .git/hooks/