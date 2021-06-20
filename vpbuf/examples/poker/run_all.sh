#!/usr/bin/bash

echo "-------" | tee out.log
./rel1/python/stack.py t.dat  4 | tee -a out.log
./rel1/nodejs/src/draw.js t.dat 2 | tee -a out.log
./rel1/cpp/build/draw t.dat 2 | tee -a out.log


echo "-------" | tee -a out.log
./rel1/nodejs/src/stack.js t.dat 7 | tee -a out.log
./rel1/cpp/build/draw t.dat 4 | tee -a out.log
./rel1/python/draw.py t.dat  3 | tee -a out.log

echo "-------" | tee -a out.log
./rel1/cpp/build/stack t.dat  5| tee -a out.log
./rel1/python/draw.py t.dat  3 | tee -a out.log
./rel1/nodejs/src/draw.js t.dat 2 | tee -a out.log


echo "-------" | tee out.log
./rel1/python/stack.py t.dat  4 | tee -a out.log
./rel2/nodejs/src/draw.js t.dat 2 | tee -a out.log
#./rel2/cpp/build/draw t.dat 2 | tee -a out.log

echo "-------" | tee out.log
./rel2/python/stack.py t.dat  4 | tee -a out.log
./rel2/nodejs/src/draw.js t.dat 2 | tee -a out.log
#./rel2/cpp/build/draw t.dat 2 | tee -a out.log