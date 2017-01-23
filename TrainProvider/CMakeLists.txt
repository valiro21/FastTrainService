project(FastTrainService)

if ("${CMAKE_BUILD_TYPE}" EQUAL "Release")
    add_definitions(-DRELEASE)
endif()

include_directories("include")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(TrainProvider SHARED ${SOURCE_FILES})

target_include_directories(TrainProvider PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)

target_link_libraries(TrainProvider neo4j-client ssl crypto Utils)