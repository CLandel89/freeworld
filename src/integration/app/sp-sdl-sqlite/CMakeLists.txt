cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem -lboost_regex")
#freeworld-impl (sdl variant) depends on this:
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lSDL2 -lSDL2_image -lSDL2_gfx")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsqlite3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L${PROJECT_SOURCE_DIR}/dist/lib/")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfreeworld-sp -lfreeworld-mpc-mps-sp -lfreeworld-mpc-sp -lfreeworld-mps-sp")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lfreeworld-integration-mpc-sp-sdl -lfreeworld-integration-mps-sp-sqlite")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl -lmruby -lm -L${PROJECT_SOURCE_DIR}/ext/mruby/build/host/lib/")

add_executable (
    "freeworld-sp-sdl-sqlite"
    "main.cpp"
)

set_target_properties(
    "freeworld-sp-sdl-sqlite"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    "${PROJECT_SOURCE_DIR}/dist/"
)

#this makes sure that the exe depends on the freeworld libs
#while the flags above solve "undefined reference" problems
#(when own libs reference mruby)
target_link_libraries (
    "freeworld-sp-sdl-sqlite"
    "freeworld-mpc-mps-sp"
    "freeworld-mpc-sp"
    "freeworld-mps-sp"
    "freeworld-sp"
    "freeworld-integration-mpc-sp-sdl"
    "freeworld-integration-mps-sp-sqlite"
)
