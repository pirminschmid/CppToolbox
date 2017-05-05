cmake_minimum_required(VERSION 3.0)
project(SimpleTemplateDemo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")

set(SOURCE_FILES main.cpp utils/KeyValueStore.cpp utils/KeyValueStore.h utils/StringHelper.cpp utils/StringHelper.h utils/TextTemplate.cpp utils/TextTemplate.h utils/TimeHelper.cpp utils/TimeHelper.h utils/Version.cpp utils/Version.h)
add_executable(template_demo ${SOURCE_FILES})
