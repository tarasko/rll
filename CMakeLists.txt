cmake_minimum_required(VERSION 2.8)

if(CMAKE_COMPILER_IS_GNUCXX)
	exec_program(
		${CMAKE_CXX_COMPILER}
		ARGS -dumpversion
		OUTPUT_VARIABLE gcc_compiler_version)

	message(STATUS "C++ compiler version: ${gcc_compiler_version} [${CMAKE_CXX_COMPILER}]")
    
	if(gcc_compiler_version VERSION_LESS "4.5.2")
		message(FATAL_ERROR "g++ version must be greater or equal to 4.5.2")
	endif(gcc_compiler_version VERSION_LESS "4.5.2")

	set(CMAKE_CXX_FLAGS "-std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(MSVC)
	if(MSVC_VERSION LESS 1600)
		message(FATAL_ERROR "MSVC version must be greater of equal to 10.0")
	endif(MSVC_VERSION LESS 1600)
endif(MSVC)

# Enumerate source files
file(GLOB src_policy src/policy/*.cpp)
file(GLOB src_value_function src/value_function/*.cpp)
file(GLOB src_detail src/detail/*.cpp)
set(src_detail_fann
	src/detail/fann/doublefann.h
	src/detail/fann/doublefann.c
	src/detail/fann/fann_cpp.h)
	
# Enumerate header files	
file(GLOB hdr rll/*.hpp)
file(GLOB hdr_policy rll/policy/*.hpp)
file(GLOB hdr_value_function rll/value_function/*.hpp)
file(GLOB hdr_detail rll/detail/*.hpp)
	
set(all_files_int 
	${hdr} ${hdr_policy} ${hdr_value_function} ${hdr_detail} 
	${src_policy} ${src_value_function} ${src_detail} ${src_detail_fann})
	
set(all_files_double ${all_files_int})

list(REMOVE_ITEM all_files_double
	"${CMAKE_CURRENT_SOURCE_DIR}/rll/value_function/lookup_table.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/value_function/lookup_table.cpp")

add_definitions(-DFANN_NO_DLL -D_CRT_SECURE_NO_WARNINGS)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(rll.int STATIC ${all_files_int})
add_library(rll.double STATIC ${all_files_double})

set_target_properties(rll.int PROPERTIES COMPILE_DEFINITIONS "RLL_INT")
set_target_properties(rll.double PROPERTIES COMPILE_DEFINITIONS "RLL_DOUBLE")

source_group(rll FILES ${hdr})
source_group(rll\\policy FILES ${hdr_policy})
source_group(rll\\value_function FILES ${hdr_value_function})
source_group(rll\\detail FILES ${hdr_detail})

source_group(src\\policy FILES ${src_policy})
source_group(src\\value_function FILES ${src_value_function})
source_group(src\\detail FILES ${src_detail})
source_group(src\\detail\\fann FILES ${src_detail_fann})

add_subdirectory(examples)
