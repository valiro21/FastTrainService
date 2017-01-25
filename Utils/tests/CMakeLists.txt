cmake_minimum_required(VERSION 3.6.2)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 14)

add_executable(Utils_tests calendar_test.cpp)

target_include_directories(Utils_tests PUBLIC $<TARGET_PROPERTY:gtest,INCLUDE_DIRECTORIES>)
target_link_libraries(Utils_tests gtest gtest_main Utils)