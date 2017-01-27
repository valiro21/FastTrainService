project(FastTrainService)

if(DOCKER_RELEASE)
    message(STATUS "TrainProvider lib detected Docker Release")
    add_definitions(-DDOCKER_RELEASE)
endif()

message(STATUS "Utils lib build type: ${CMAKE_BUILD_TYPE}")
add_definitions("-D${CMAKE_BUILD_TYPE}")
get_directory_property( DirDefs DIRECTORY "./" COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "Found Define: " ${d} )
endforeach()

include_directories(include)

add_definitions (-Wmultichar)

add_subdirectory(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB SOURCE_FILES src/*.cpp)

add_library(Utils SHARED ${SOURCE_FILES})