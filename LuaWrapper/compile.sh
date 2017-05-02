#!/bin/bash
# builds a C++ sample project that uses an embedded Lua interpreter
# including compilation of lua
# depends on lua being installed before using the install_lua.sh script
current_path=$(pwd)
code_source_path=$current_path/src/SampleProject
example_scripts_source_path=$code_source_path/example_scripts
target_path=$current_path/bin
build_path=$target_path/build
lua_source_path=$current_path/lua
export LUA_TARGET_PATH=$target_path/lua
export LUA_INCLUDE_PATH=$code_source_path/lua
export LUA_LIB_PATH=$LUA_TARGET_PATH/lib
#
if [ -f $lua_source_path/Makefile ]; then
    echo "Lua Makefile detected."
else
    echo "Lua Makefile not found. Please use ./install_lua.sh first."
    exit 1
fi
#
mkdir -p $target_path 
rm -rf $target_path/* 2>/dev/null
mkdir -p $build_path
rm -r $build_path/* 2>/dev/null
mkdir -p $LUA_INCLUDE_PATH
rm -r $LUA_INCLUDE_PATH/* 2>/dev/null
#
echo "compilation of Lua from $lua_source_path to $LUA_TARGET_PATH"
cp -r $lua_source_path $LUA_TARGET_PATH
cd $LUA_TARGET_PATH
if [ "$1" = "mac" ]; then
    make macosx
else
    make linux
fi
make install
echo "installing of includes to $LUA_INCLUDE_PATH; liblua.a is in $LUA_LIB_PATH"
cp $LUA_TARGET_PATH/include/* $LUA_INCLUDE_PATH/
#
echo "compilation of Sample program from $code_source_path in $build_path"
cd $build_path
cmake $code_source_path
make sample_project
cd $current_path
echo "installing binaries to $target_path"
cp $build_path/sample_project $target_path/
echo "installing script examples from $template_source_path to $target_path"
cp $example_scripts_source_path/*.lua $target_path/ 
echo "complete: all needed files are in $target_path"
#
echo "see ./bin/sample_project and ./bin/test1.lua"
