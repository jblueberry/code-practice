cmake_minimum_required(VERSION 3.0)

project(dslabs-cpp)

# use c++ 20
set(CMAKE_CXX_STANDARD 20)

add_library(dslabs INTERFACE)
target_include_directories(dslabs INTERFACE include)

add_subdirectory(test)
