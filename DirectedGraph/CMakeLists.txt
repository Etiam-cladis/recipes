cmake_minimum_required(VERSION 3.24)

project(DG)

SET(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(dg_test
    test.cpp)

add_subdirectory(src)

target_link_libraries(dg_test
    dg_impl
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(dg_test)
