cmake_minimum_required(VERSION 3.0)
project(StatisticsHelper)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")

set(SOURCE_FILES validate_statistics_module.cpp toolbox/StatisticsHelper.cpp toolbox/StatisticsHelper.h)
add_executable(validate_statistics_module ${SOURCE_FILES})
