add_executable(unit_test unit_tests.cpp)

target_link_libraries(unit_test GTest::gtest_main)
target_link_libraries(unit_test trianglelib)

include(GoogleTest)
gtest_discover_tests(unit_test)