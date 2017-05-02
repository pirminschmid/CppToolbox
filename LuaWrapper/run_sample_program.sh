#!/bin/bash
# run the example
#
if [ -f ./bin/sample_project ]; then
    echo "OK ./bin/sample_project found."
else
    echo "./bin/sample_project not found. Please use ./compile.sh first."
    exit 1
fi
if [ -f ./bin/test1.lua ]; then
    echo "OK ./bin/test1.lua not found."
else
    echo "./bin/test1.lua not found. Please use ./compile.sh first."
    exit 1
fi
#
cd bin
echo "running ./sample_project test1.lua"
./sample_project test1.lua
