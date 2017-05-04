cmake_minimum_required(VERSION 3.0)
project(SampleProject)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++14 -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-std=c++14 -Wall -O2")

link_directories($ENV{LUA_LIB_PATH})

set(LUA_INCLUDES lua/lua.hpp lua/lua.h lua/lualib.h lua/lauxlib.h lua/luaconf.h)

set(UTILS utils/LuaWrapper.cpp utils/LuaWrapper.h ${LUA_INCLUDES})

set(SOURCE_FILES main.cpp ${LUA_INCLUDES} ${UTILS})
add_executable(sample_project ${SOURCE_FILES})
target_link_libraries(sample_project lua)
target_link_libraries(sample_project dl)
