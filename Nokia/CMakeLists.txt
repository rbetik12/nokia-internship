﻿# CMakeList.txt : CMake project for Nokia, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (CSVParser "Nokia.cpp"  "CSVParser.h" "CSVParser.cpp" "Exceptions.h")

# TODO: Add tests and install targets if needed.
