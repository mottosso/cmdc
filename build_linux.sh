#!/usr/bin/env bash

# requires python
# requires g++ (7.3.1)
# requires $DEVKIT_LOCATION

round() {
  printf "%.${2}f" "${1}"
}

CMDC_VERSION="0.1.1"

t0=$(date +%s.%N)

echo "(1) Parsing.."
python ./scripts/mfn.py parse

if [ $? -ne 0 ]; then
    exit 1
fi

t1=$(date +%s.%N)
parse_duration=$(echo "(($t1 - $t0) * 1000)/1" | bc)

echo "(1) Finished in $parse_duration ms"
echo "(1) ----------------------------"
echo "(2) Compiling.."

# Make build directory, unless one already exists
mkdir -p build

g++ src/main.cpp \
    -I$DEVKIT_LOCATION/include \
    -I$DEVKIT_LOCATION/include/Python \
    -L$DEVKIT_LOCATION/lib \
    -L$(pwd)/lib \
    -I$(pwd)/include \
    -std=c++11 \
    -o build/main.o \
    -o build/cmdc.so \
    -w \
    -shared \
    -fPIC \
    -fexceptions \
    -lstdc++ \
    -lpython2.7 \
    -lFoundation \
    -lOpenMaya \
    -lOpenMayaRender \
    -lOpenMayaUI \
    -lOpenMayaAnim \
    -lOpenMayaFX \
    -DNDEBUG \
    -DVERSION_INFO=$CMDC_VERSION

if [ $? -ne 0 ]; then
    exit 1
fi

t2=$(date +%s.%N)
compile_duration=$(echo "(($t2 - $t1) * 1000)/1" | bc)

echo "(2) Finished in $compile_duration ms"
echo "(2) ----------------------------"
echo "(3) Cleaning.."

python ./scripts/mfn.py clean

t3=$(date +%s.%N)
clean_duration=$(echo "(($t3 - $t2) * 1000)/1" | bc)
total_duration=$(echo "(($t3 - $t0) * 1000)/1" | bc)

echo "(3) Finished in $clean_duration ms"
echo "(3) ----------------------------"
echo "Successfully created ./build/cmdc.so in $total_duration ms"
