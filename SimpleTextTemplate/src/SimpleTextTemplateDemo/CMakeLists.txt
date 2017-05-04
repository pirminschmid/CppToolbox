cmake_minimum_required(VERSION 3.0)
project(SimpleTemplateDemo)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp utils/KeyValueStore.cpp utils/KeyValueStore.h utils/StringHelper.cpp utils/StringHelper.h utils/TextTemplate.cpp utils/TextTemplate.h utils/TimeHelper.cpp utils/TimeHelper.h)
add_executable(template_demo ${SOURCE_FILES})