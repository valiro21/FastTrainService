cmake_minimum_required(VERSION 3.6)
project(FastTrainService)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES src/Server/main.cpp src/Server/ClientThread.cpp src/Server/ClientThread.hpp src/Server/JThread.cpp include/JThread.hpp src/Server/Utils.cpp include/Utils.hpp src/Server/Logger.cpp include/Logger.hpp src/Server/RequestsPool.cpp src/Server/RequestsPool.hpp src/Server/RequestWorker.cpp src/Server/RequestWorker.hpp src/Server/RequestTaskFactory.cpp src/Server/RequestTaskFactory.hpp src/Server/Server.cpp include/Server.hpp src/Server/RequestTask.hpp src/Server/DatabaseManager.cpp include/DatabaseManager.h src/Server/ArrivalsRequest.cpp src/Server/ArrivalsRequest.hpp src/Server/DeparturesRequest.cpp src/Server/DeparturesRequest.hpp src/Server/PathFinderRequest.cpp src/Server/PathFinderRequest.hpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lneo4j-client -lssl -lcrypto")

add_executable(FastTrainServer ${SOURCE_FILES})