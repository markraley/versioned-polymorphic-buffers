cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE_ON)

project(vectors_example)

set(sources
		../src/vectors.cc
	)

add_executable(vectors ${sources})

target_include_directories(vectors PUBLIC
		$ENV{vpc_dir}
	)