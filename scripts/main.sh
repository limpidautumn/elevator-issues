#!/bin/bash
cd "$(dirname "${BASH_SOURCE[0]}")/../"
[ -d "./temp/" ] && sudo rm -rf ./temp/; mkdir ./temp/
[ -d "./result/" ] && sudo rm -rf ./result/; mkdir ./result/

if [ $# -eq 0 ]; then
    echo "No input data path provided."
    exit 1
fi

g++ ./src/*.cpp -o ./temp/main.out -I ./include/ -lfftw3l -lm -Wall -Wextra -std=c++17 -O2
./temp/main.out "$1"

for csv_file in ./result/*.csv; do
    if [ -f "$csv_file" ]; then
        sudo python3 ./src/plotting.py "$csv_file"
    fi
done

echo "Done."
