#!/bin/bash

# Deprecated.

cd "$(dirname "${BASH_SOURCE[0]}")/../"
[ -d "./temp/" ] || mkdir ./temp/

[ -f "/usr/local/include/fftw3.h" ] && exit 0

(
curl -Lo ./temp/fftw3.tar.gz https://www.fftw.org/fftw-3.3.10.tar.gz &> /dev/null
tar -xzf ./temp/fftw3.tar.gz -C ./temp/ &> /dev/null
cd ./temp/fftw-3.3.10/
./configure &> /dev/null
make &> /dev/null
make install &> /dev/null
)

rm -rf ./temp/
