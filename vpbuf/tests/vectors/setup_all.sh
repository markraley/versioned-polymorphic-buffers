#!/usr/bin/bash

if [ ! -d "./python/out" ]; then
	mkdir ./python/out
fi

if [ ! -d "./nodejs/out" ]; then
	mkdir ./nodejs/out
fi

if [ ! -d "./cpp/out" ]; then
	mkdir ./cpp/out
fi

if [ ! -d "./cpp/build" ]; then
	mkdir ./cpp/build
fi

pushd .

cd ./cpp/build
cmake ..
cmake --build .

popd
