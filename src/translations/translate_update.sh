#!/bin/sh
# this file is used to auto-update .ts file.

cd "$(dirname "$0")" || exit

for ts in ./*.ts; do
#    printf "\nprocess ${ts}\n"
    lupdate ../../src -recursive -no-obsolete -ts "${ts}"
done
