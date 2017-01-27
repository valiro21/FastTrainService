cmake_minimum_required(VERSION 3.5)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory("lib/googletest")
add_subdirectory("Utils")
add_subdirectory("TrainProvider")
add_subdirectory("Server")
add_subdirectory("Client")