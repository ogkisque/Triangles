cmake_minimum_required(VERSION 3.11)
project(triangle)

option(WITH_UNIT_TESTS "unit tests" OFF)
option(WITH_BENCHMARKS "benchmarks" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=leak,address,undefined")

add_subdirectory(src)

if (WITH_UNIT_TESTS)
    include(FetchContent)

    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    message("Build binary file for UNIT tests ...")
    add_subdirectory(tests)
endif()

if (WITH_BENCHMARKS)
    add_subdirectory(benchs)
endif()