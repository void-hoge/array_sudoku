cmake_minimum_required(VERSION 3.10)
project(2048 CXX)
set(CMAKE_CXX_FLAGS "-std=c++14 -O3 -mtune=native -march=native -mavx2 -msse4.2")
add_executable(a.out main.cpp board.cpp solver.cpp)
