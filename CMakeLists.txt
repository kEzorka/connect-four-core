cmake_minimum_required(VERSION 3.10.0)
project(connect-four-core)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/includes/*.h"
    "${CMAKE_SOURCE_DIR}/lib/*.h"
    "${CMAKE_SOURCE_DIR}/lib/*.hpp"
)

add_executable(connect-four-core ${SOURCES})
