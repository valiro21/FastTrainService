project(FastTrainService)

include_directories(include)

add_definitions (-Wmultichar)

add_subdirectory(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

file(GLOB SOURCE_FILES src/*.cpp)

add_library(Utils SHARED ${SOURCE_FILES})