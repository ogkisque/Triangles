set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libhayai/src)

add_executable(benchs benchs.cpp)
target_link_libraries(benchs geometry)

target_include_directories(benchs PUBLIC ${INCLUDE_DIR})