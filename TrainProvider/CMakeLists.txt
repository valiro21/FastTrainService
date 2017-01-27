project(FastTrainService)

add_subdirectory(tests)

message(STATUS "TrainProvider lib build type: ${CMAKE_BUILD_TYPE}")
add_definitions("-D${CMAKE_BUILD_TYPE}")
get_directory_property( DirDefs DIRECTORY "./" COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "Found Define: " ${d} )
endforeach()
message( STATUS "DirDefs: " ${DirDefs} )

include_directories("include")

file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_library(TrainProvider SHARED ${SOURCE_FILES} src/Providers/MultiQueryProvider.cpp src/Providers/MultiQueryProvider.hpp src/Providers/ShortestPathProvider.cpp src/Providers/ShortestPathProvider.hpp src/Providers/UpdateProvider.cpp src/Providers/UpdateProvider.hpp src/Providers/UpdateDelay.cpp src/Providers/UpdateDelay.hpp src/Providers/DelayResetProvider.cpp src/Providers/DelayResetProvider.hpp)

target_include_directories(TrainProvider PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)

target_link_libraries(TrainProvider neo4j-client ssl crypto Utils)