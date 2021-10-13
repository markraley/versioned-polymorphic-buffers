cmake_minimum_required(VERSION 3.16)
set(CMAKE_VERBOSE_MAKEFILE_ON)

project(vpbuf_compiler)

set(vpbuf_src_dir $ENV{vpdir})
set(boost_dir $ENV{BOOST})
set(sources
		${vpbuf_src_dir}/compiler/src/vpc.cc

		${vpbuf_src_dir}/compiler/src/pod/pod_varint.cc
		${vpbuf_src_dir}/compiler/src/pod/pod_vector.cc
		${vpbuf_src_dir}/compiler/src/pod/pod_map.cc
		${vpbuf_src_dir}/compiler/src/pod/pod_typed.cc
		${vpbuf_src_dir}/compiler/src/pod/pod_string.cc

		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_varint.cc
		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_pod.cc
		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_reorder_pod.cc
		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_vector.cc
		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_poly.cc
		${vpbuf_src_dir}/compiler/src/vp_typedef/vp_typedef_string.cc
	)

add_executable(vpc ${sources})
set_property(TARGET vpc PROPERTY CXX_STANDARD 17)

target_compile_options(vpc PUBLIC -w -fpermissive)
target_include_directories(vpc PUBLIC
		${boost_dir}/boost/boost_1_46_1
		${vpbuf_src_dir}/compiler/src
		${vpbuf_src_dir}/compiler/src/pod
		${vpbuf_src_dir}/compiler/src/vp_typedef
	)