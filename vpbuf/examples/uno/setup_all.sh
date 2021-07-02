#!/usr/bin/bash

if [ ! -d "./rel1/cpp/build" ]; then
	mkdir ./rel1/cpp/build
	pushd ./rel1/cpp/build
	cmake ..
	popd
fi

vpc ./rel1/uno.vpc

pushd ./rel1/cpp/build
cmake --build .
popd

