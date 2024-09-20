set(/home/ask0later/vladimirov/Triangles/include)

include_directories(/home/ask0later/vladimirov/Triangles/include)
add_executable(unit_test unit_tests.cpp)

target_link_libraries(unit_test GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(unit_test)