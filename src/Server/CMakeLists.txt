project(FastTrainService)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lneo4j-client -lssl -lcrypto")

set(SOURCE_FILES
        ${SOURCE_FILES}
        main.cpp
        Server.cpp
        ClientThread.cpp ClientThread.hpp
        RequestsPool.cpp RequestsPool.hpp
        RequestWorker.cpp RequestWorker.hpp
        Requests/RequestTaskFactory.cpp Requests/RequestTaskFactory.hpp
        Requests/RequestTask.hpp
        DatabaseManager.cpp DatabaseManager.h
        Requests/ArrivalsRequest.cpp Requests/ArrivalsRequest.hpp
        Requests/DeparturesRequest.cpp Requests/DeparturesRequest.hpp
        Requests/PathFinderRequest.cpp Requests/PathFinderRequest.hpp Requests/AutocompleteRequest.cpp Requests/AutocompleteRequest.hpp)

set(EXECUTABLE_OUTPUT_PATH ../../bin/${CMAKE_BUILD_TYPE})

add_executable(FastTrainServer ${SOURCE_FILES})