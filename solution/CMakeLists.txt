cmake_minimum_required(VERSION 3.24)

project(solution_test)

SET(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(solution
    solution.cpp)

add_library(fraction
    fraction.cpp)

enable_testing()

add_executable(f_test
    fraction_test.cpp)

target_link_libraries(f_test
    fraction
    GTest::gtest_main
)

add_executable(s_test
    solution_test.cpp)

target_link_libraries(s_test
    solution
    fraction
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(s_test)
gtest_discover_tests(f_test)
