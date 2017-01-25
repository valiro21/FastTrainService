cmake_minimum_required(VERSION 3.6.2)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server_tests ../src/Server.cpp ../src/ClientThread.cpp ServerTest.cpp)

target_include_directories(Server_tests PUBLIC $<TARGET_PROPERTY:TrainProvider,INCLUDE_DIRECTORIES>)
target_include_directories(Server_tests PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)
target_include_directories(Server_tests PUBLIC $<TARGET_PROPERTY:gtest,INCLUDE_DIRECTORIES>)
target_link_libraries(Server_tests gtest gtest_main Utils TrainProvider)