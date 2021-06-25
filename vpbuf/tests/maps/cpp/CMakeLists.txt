cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE_ON)

project(maps_example)

set(sources
		../src/maps.cc
	)

add_executable(maps ${sources})
