cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lmruby -lm -L${PROJECT_SOURCE_DIR}/ext/mruby/build/host-debug/lib/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${PROJECT_SOURCE_DIR}/ext/mruby/include/")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/dist/lib/")

add_library (
    "freeworld-mps-sp"
    SHARED
    "instance.cpp"
    "instance-private.cpp"
    "core_utils.cpp"
    "database.cpp"
)
