#!/bin/bash
#installs the desired Lua version at the proper place here in the project
lua_name=lua-5.3.4
current_path=$(pwd)
code_source_path=$current_path/src/SampleProject
target_path=$current_path/bin
build_path=$target_path/build
lua_source_path=$current_path/lua
export LUA_TARGET_PATH=$target_path/lua
export LUA_INCLUDE_PATH=$code_source_path/lua
export LUA_LIB_PATH=$LUA_TARGET_PATH/lib
# get Lua
curl -R -O http://www.lua.org/ftp/$lua_name.tar.gz
tar zxf lua-5.3.4.tar.gz
rm -rf lua
mv $lua_name lua
cd lua
mv Makefile Makefile_original
sed -e "s/\/usr\/local/\$(LUA_TARGET_PATH)/g" Makefile_original > Makefile
if [ "$1" = "mac" ]; then
    make macosx test
else
    make linux test
fi
make install
echo "installing of includes to $LUA_INCLUDE_PATH; liblua.a is in $LUA_LIB_PATH"
mkdir -p $LUA_INCLUDE_PATH
cp $LUA_TARGET_PATH/include/* $LUA_INCLUDE_PATH/
cd ..
