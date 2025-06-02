#!/bin/bash
cd "$(dirname "${BASH_SOURCE[0]}")/../"

echo "Updating apt..."
sudo apt update -qq &> /dev/null
sudo apt upgrade -y -qq &> /dev/null
echo "✓ OK"

echo "Installing build-essential..."
sudo apt install build-essential -y -qq &> /dev/null
command -v g++ &> /dev/null && echo "✓ build-essential SUCCESS" || echo "✗ build-essential FAILED" >&2

echo "Installing clang-format..."
sudo apt install clang-format -y -qq &> /dev/null
command -v clang-format &> /dev/null && echo "✓ clang-format SUCCESS" || echo "✗ clang-format FAILED" >&2

echo "Installing CMake..."
sudo apt install cmake -y -qq &> /dev/null
command -v cmake &> /dev/null && echo "✓ CMake SUCCESS" || echo "✗ CMake FAILED" >&2

echo "Installing Python3..."
sudo apt install python3 -y -qq &> /dev/null
command -v python3 &> /dev/null && echo "✓ Python3 SUCCESS" || echo "✗ Python3 FAILED" >&2

echo "Installing Python3-matplotlib..."
sudo apt install python3-matplotlib -y -qq &> /dev/null
python3 -c "import matplotlib" &> /dev/null && echo "✓ Python3-matplotlib SUCCESS" || echo "✗ Python3-matplotlib FAILED" >&2

echo "Installing Python3-pandas..."
sudo apt install python3-pandas -y -qq &> /dev/null
python3 -c "import pandas" &> /dev/null && echo "✓ Python3-pandas SUCCESS" || echo "✗ Python3-pandas FAILED" >&2

# Deprecated.
# echo "Installing fftw3..."
# sudo ./scripts/fftw3-install.sh
# [ -f "/usr/local/include/fftw3.h" ] && echo "✓ fftw3 SUCCESS" || echo "✗ fftw3 FAILED" >&2

echo "Installing fftw3..."
sudo apt install libfftw3-dev libfftw3-long3 -y -qq &> /dev/null
[ -f "/usr/include/fftw3.h" ] && echo "✓ fftw3 SUCCESS" || echo "✗ fftw3 FAILED" >&2

echo "Cleaning up..."
sudo apt autoremove -y -qq &> /dev/null
sudo apt clean -qq &> /dev/null
