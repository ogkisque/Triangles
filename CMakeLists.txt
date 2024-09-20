cmake_minimum_required(VERSION 3.11)
project(triangle)

option(WITH_TEST "unit tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

if (WITH_TESTS)
    message("Build binary file for UNIT tests ...")
    add_subdirectory(tests)
endif()