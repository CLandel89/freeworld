cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem -lboost_regex")
#freeworld-impl (sdl variant) depends on this:
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lSDL2 -lSDL2_image -lSDL2_gfx")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsqlite3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${PROJECT_SOURCE_DIR}/dist/lib/")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfreeworld-sp -lfreeworld-common -lfreeworld-common-mpc-sp -lfreeworld-common-mps-sp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfreeworld-sdl -lfreeworld-sqlite")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl -lmruby -lm -L${PROJECT_SOURCE_DIR}/ext/mruby/build/host/lib/")

add_executable (
    "freeworld-sp-default"
    "main.cpp"
)

set_target_properties(
    "freeworld-sp-default"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/dist/"
)

#this makes sure that the exe depends on the freeworld libs
#while the flags above solve "undefined reference" problems
#(when own libs reference mruby)
target_link_libraries (
    "freeworld-sp-default"
    "freeworld-common"
    "freeworld-common-mpc-sp"
    "freeworld-common-mps-sp"
    "freeworld-sdl"
    "freeworld-sqlite"
    "freeworld-sp"
)
