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

enable_testing()

add_executable(s_test
    solution_test.cpp)

target_link_libraries(s_test
    solution
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(s_test)
