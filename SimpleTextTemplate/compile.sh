#!/bin/bash
# builds a C++ sample project
current_path=$(pwd)
code_source_path=$current_path/src/SimpleTextTemplateDemo
templates_path=$current_path/templates
target_path=$current_path/bin
build_path=$target_path/build
#
mkdir -p $target_path 
rm -rf $target_path/* 2>/dev/null
mkdir -p $build_path
rm -r $build_path/* 2>/dev/null
#
cd $build_path
cmake $code_source_path
make
cd $current_path
echo "installing binaries to $target_path"
cp $build_path/template_demo $target_path/
echo "installing templates to $target_path"
cp $templates_path/* $target_path/
