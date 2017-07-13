#!/bin/bash


# 失败就退出
rm -rf build
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug  .. || exit 1
make  || exit 1

cd ..
rm -rf build
./encodingdemo || exit 1