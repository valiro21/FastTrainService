project(FastTrainService)

message(STATUS "Server build type: ${CMAKE_BUILD_TYPE}")
add_definitions("-D${CMAKE_BUILD_TYPE}")
get_directory_property( DirDefs DIRECTORY "./" COMPILE_DEFINITIONS )
foreach( d ${DirDefs} )
    message( STATUS "Found Define: " ${d} )
endforeach()
message( STATUS "DirDefs: " ${DirDefs} )

include_directories(include)

add_subdirectory(tests)

set(SOURCE_FILES
        ${SOURCE_FILES}
        src/main.cpp
        src/Server.cpp
        src/ClientThread.cpp)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_executable(FastTrainServer ${SOURCE_FILES})

target_include_directories(FastTrainServer PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)
target_include_directories(FastTrainServer PUBLIC $<TARGET_PROPERTY:TrainProvider,INCLUDE_DIRECTORIES>)

target_link_libraries(FastTrainServer TrainProvider Utils)