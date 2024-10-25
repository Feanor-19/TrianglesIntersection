cmake_minimum_required(VERSION 3.11)
project(Triangles)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(SRC_DIR src)

add_executable(Driver ${SRC_DIR}/main.cpp)
target_include_directories(Driver PUBLIC inc)