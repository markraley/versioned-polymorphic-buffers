cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE_ON)

project(poker_example)

set(sources
		../src/stack.cc
	)

set(draw_sources
		../src/draw.cc
	)

add_executable(stack ${sources})
add_executable(draw ${draw_sources})
