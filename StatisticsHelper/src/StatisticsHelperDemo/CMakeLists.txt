cmake_minimum_required(VERSION 3.0)
project(StatisticsHelper)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES validate_statistics_module.cpp utils/StatisticsHelper.cpp utils/StatisticsHelper.h)
add_executable(validate_statistics_module ${SOURCE_FILES})
