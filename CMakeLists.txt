cmake_minimum_required(VERSION 2.6)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/impl/mpc-sp/sdl/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app/sp/default/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app/mpc/default/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/app/mps/default/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/common/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/common-mpc-sp/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/common-mps-sp/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/mpc/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/mps/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/sp/)
