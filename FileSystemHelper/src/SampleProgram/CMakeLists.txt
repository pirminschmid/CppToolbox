cmake_minimum_required(VERSION 3.0)
project(SampleProgram)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")

set(SOURCE_FILES main.cpp utils/FileSystemHelper.cpp utils/FileSystemHelper.h)
add_executable(sample_program ${SOURCE_FILES})
