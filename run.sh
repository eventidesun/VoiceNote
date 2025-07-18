#!/bin/bash

echo "Cleaning build directory..."
rm -rf cmake-build-debug

echo "Configuring with CMake..."
cmake -DCMAKE_PREFIX_PATH=/usr/local/opt/qt@5 -B cmake-build-debug

echo "Building project..."
cmake --build cmake-build-debug --target group08_app

if [ -f ./cmake-build-debug/group08_app ]; then
  echo "Running app..."
  ./cmake-build-debug/group08_app
else
  echo "Build failed: group08_app not found."
fi
