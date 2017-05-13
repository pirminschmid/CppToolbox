cmake_minimum_required(VERSION 3.0)
project(SimpleTemplateDemo)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")

set(TOOLBOX toolbox/KeyValueStore.cpp toolbox/KeyValueStore.h toolbox/StringHelper.cpp toolbox/StringHelper.h toolbox/TextTemplate.cpp toolbox/TextTemplate.h toolbox/TimeHelper.cpp toolbox/TimeHelper.h toolbox/Version.cpp toolbox/Version.h)
set(SOURCE_FILES main.cpp ${TOOLBOX})
add_executable(template_demo ${SOURCE_FILES})
