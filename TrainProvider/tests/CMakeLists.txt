cmake_minimum_required(VERSION 3.6.2)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 14)


set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})
add_executable(TrainProvider_tests database_tests.cpp)

target_include_directories(TrainProvider_tests PUBLIC $<TARGET_PROPERTY:TrainProvider,INCLUDE_DIRECTORIES>)
target_link_libraries(TrainProvider_tests gtest gtest_main TrainProvider)