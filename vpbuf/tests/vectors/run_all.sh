#!/usr/bin/bash

pushd .

echo 'running python tests'
cd python
python3 ./vectors.py
cd ..
echo

echo 'running nodejs tests'
cd nodejs
nodejs ./src/vectors.js
cd ..
echo

echo 'running cplusplus tests'
cd cpp
./build/vectors
cd ..
echo

popd