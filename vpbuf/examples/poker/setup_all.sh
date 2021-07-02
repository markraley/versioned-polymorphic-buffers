#!/usr/bin/bash

if [ ! -d "./rel1/cpp/build" ]; then
	mkdir ./rel1/cpp/build
	pushd ./rel1/cpp/build
	cmake ..
	popd
fi

vpc ./rel1/poker.vpc

pushd ./rel1/cpp/build
cmake --build .
popd

# ----------------------------------------------------------------------

if [ ! -d "./rel2/cpp/build" ]; then
	mkdir ./rel2/cpp/build
	pushd ./rel2/cpp/build
	cmake ..
	popd
fi

vpc ./rel2/poker.vpc

pushd ./rel2/cpp/build
cmake --build .
popd

