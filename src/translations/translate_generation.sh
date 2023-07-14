#!/bin/sh
# this file is used to auto-generate .qm file from .ts file.

cd "$(dirname "$0")" || exit

for ts in ./*.ts; do
#    printf "\nprocess ${ts}\n"
    lrelease "${ts}"
done
