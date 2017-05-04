cmake_minimum_required(VERSION 3.0)
project(SampleProgram)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp utils/LinkedMap.cpp utils/LinkedMap.h)
add_executable(sample_program ${SOURCE_FILES})
