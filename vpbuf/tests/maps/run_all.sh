#!/usr/bin/bash

pushd .

echo 'running python tests'
cd python
python3 ./maps.py
cd ..
echo

echo 'running nodejs tests'
cd nodejs
nodejs ./src/maps.js
cd ..
echo

echo 'running cplusplus tests'
cd cpp
./build/maps
cd ..
echo

popd
