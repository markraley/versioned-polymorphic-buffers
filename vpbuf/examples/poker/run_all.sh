#!/usr/bin/bash

echo "python"
./rel1/python/stack.py t.dat
./rel1/python/draw.py t.dat

echo
echo "nodejs"
./rel1/nodejs/src/stack.js t.dat
./rel1/nodejs/src/draw.js t.dat

echo
echo "cpp"
./rel1/cpp/build/stack t.dat
./rel1/cpp/build/draw t.dat