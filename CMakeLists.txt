cmake_minimum_required(VERSION 3.5)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(src)

if(CMAKE_BUILD_TYPE == "RELEASE")
    add_definitions(-DRELEASE)
else()
    add_definitions(-DDEBUG)

file(GLOB SOURCE_FILES include/*.hpp )
file(GLOB SOURCE_FILES src/*.cpp )
add_subdirectory("src/Server")

set (SOURCE_FILES )
file(GLOB SOURCE_FILES include/*.hpp )
file(GLOB SOURCE_FILES src/*.cpp )
add_subdirectory("src/Client")