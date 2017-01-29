cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../dist/lib/")

add_library (
    "jumpfree-common"
    SHARED
    "utils.cpp"
)
