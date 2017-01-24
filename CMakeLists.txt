cmake_minimum_required(VERSION 3.5)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 14)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    add_definitions(-DRELEASE)
else()
    add_definitions(-DDEBUG)
endif()

add_subdirectory("lib/googletest")
add_subdirectory("Utils")
add_subdirectory("TrainProvider")
add_subdirectory("TrainProvider_tests")
add_subdirectory("Server")
add_subdirectory("Client")