cmake_minimum_required(VERSION 3.11)
project(Triangles)
include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(SRC_DIR src)

add_library(TrianglesLib ${SRC_DIR}/triangles.cpp)
target_include_directories(TrianglesLib PUBLIC inc)

add_executable(Driver ${SRC_DIR}/main.cpp)
target_include_directories(Driver PUBLIC inc)
target_link_libraries(Driver TrianglesLib)

# Unit tests with GTest
find_package(GTest REQUIRED)

add_executable(UnitTests ${SRC_DIR}/unit_tests.cpp)
target_include_directories(UnitTests PUBLIC inc)
target_link_libraries(UnitTests gtest::gtest)
target_link_libraries(UnitTests TrianglesLib)

include(GoogleTest)
gtest_discover_tests(UnitTests)