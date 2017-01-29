cmake_minimum_required(VERSION 2.6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lboost_filesystem -lboost_regex")
#jumpfree-impl (sdl variant) depends on this:
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lSDL2 -lSDL2_image -lSDL2_gfx")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L../../../../dist/lib/")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ljumpfree-sp -ljumpfree-common -ljumpfree-common-mpc-sp -ljumpfree-common-mps-sp -ljumpfree-sdl")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl -lmruby -lm -L../../../../ext/mruby/build/host/lib/")

add_executable (
    "jumpfree-sp-default"
    "main.cpp"
)

set_target_properties(
    "jumpfree-sp-default"
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    "../../../../dist/"
)

#this makes sure that the exe depends on the jumpfree libs
#while the flags above solve "undefined reference" problems
#(when own libs reference mruby)
target_link_libraries (
    "jumpfree-sp-default"
    "jumpfree-common"
    "jumpfree-common-mpc-sp"
    "jumpfree-common-mps-sp"
    "jumpfree-sdl"
    "jumpfree-sp"
)
