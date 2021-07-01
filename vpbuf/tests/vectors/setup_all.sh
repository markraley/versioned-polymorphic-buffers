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
	pushd ./cpp/build
	cmake ..
	popd
fi

vpc vectors.vpc

pushd ./cpp/build
cmake --build .
popd
