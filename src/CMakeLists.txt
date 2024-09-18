set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(geometry geometry.cpp)
target_include_directories(geometry PUBLIC ${INCLUDE_DIR})