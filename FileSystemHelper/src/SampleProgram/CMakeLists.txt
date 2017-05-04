cmake_minimum_required(VERSION 3.0)
project(SampleProgram)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp utils/FileSystemHelper.cpp utils/FileSystemHelper.h)
add_executable(sample_program ${SOURCE_FILES})