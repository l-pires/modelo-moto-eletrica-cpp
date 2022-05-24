#!/bin/sh

rm -rf ./build
mkdir build
cd src
make
cp origem-ps ../build/origem-ps
make clean
cd ..