set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
cmake_minimum_required(VERSION 3.6)
project(doublelist)
add_executable(TESTER test.cpp)
include_directories("../../src")
