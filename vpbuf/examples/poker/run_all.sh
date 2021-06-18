#!/usr/bin/bash

echo "" | tee out.log
./rel1/python/stack.py t.dat  9 | tee -a out.log
./rel1/nodejs/src/draw.js t.dat 3 | tee -a out.log
./rel1/cpp/build/draw t.dat 2 | tee -a out.log
./rel1/python/draw.py t.dat  4 | tee -a out.log

echo "" | tee -a out.log
./rel1/nodejs/src/stack.js t.dat | tee -a out.log
./rel1/nodejs/src/draw.js t.dat | tee -a out.log

echo "" | tee -a out.log
./rel1/cpp/build/stack t.dat | tee -a out.log
./rel1/cpp/build/draw t.dat | tee -a out.log