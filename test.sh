#! /bin/bash

BRANCH_NAME="$(git rev-parse --abbrev-ref HEAD)"
echo "${BRANCH_NAME}"