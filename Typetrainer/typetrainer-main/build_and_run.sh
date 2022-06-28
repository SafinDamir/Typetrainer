#!/bin/bash
mkdir build
mkdir texts
cd build
cmake ../src
touch errors
make
./tt 2>errors
