cmake_minimum_required(VERSION 3.24)
project(Lab7)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(Lab7 main.cpp functions.cpp)
