#!/bin/bash

AUTO_CONFIRM=false

for arg in "$@"
do
    if [[ "$arg" == "-y" ]]; then
        AUTO_CONFIRM=true
    fi
done

git add .
git clean -xdn

if [ "$AUTO_CONFIRM" = false ]; then
    read -p "Confirm deletion? (y/n) " -n 1 -r
    echo ""
    if [[ ! $REPLY =~ ^[Yy]$ ]]
    then
        echo "Operation canceled."
        exit 1
    fi
else
    echo "Auto-confirmed deletion. (-y flag set)"
fi

git clean -xdf
