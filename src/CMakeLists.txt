set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_library(trianglelib INTERFACE)
target_include_directories(trianglelib INTERFACE ${INCLUDE_DIR})

add_executable(main main.cpp)
target_link_libraries(main trianglelib)