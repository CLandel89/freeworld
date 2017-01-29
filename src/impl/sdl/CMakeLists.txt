cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lSDL2 -lSDL2_image -lSDL2_gfx")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "../../../dist/lib")

add_library(
    "jumpfree-sdl"
    SHARED
    "sdl.cpp"
)
