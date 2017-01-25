project(FastTrainService)

include_directories(..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lneo4j-client -lssl -lcrypto")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Location REQUIRED )

qt5_wrap_cpp(FastTrainClientWrap src/CitySelector.hpp)
qt5_wrap_cpp(FastTrainClientWrap src/Tables/RoutesTable.hpp)
qt5_wrap_cpp(FastTrainClientWrap src/Tables/DeparturesTable.hpp)
qt5_wrap_cpp(FastTrainClientWrap src/Tables/ArrivalsTable.hpp)
qt5_wrap_cpp(FastTrainClientWrap src/ArrivalsTab.hpp)
qt5_wrap_cpp(FastTrainClientWrap src/DeparturesTab.hpp)

set(SOURCE_FILES
        src/main.cpp
        src/DateSelector.cpp
        src/CitySelector.cpp
        ${FastTrainClientWrap}
        src/Client.cpp
        src/Tables/ArrivalsTable.cpp
        src/ArrivalsTab.cpp
        src/DeparturesTab.cpp
        src/WidgetFactory.cpp
        src/Tables/DeparturesTable.cpp)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_executable(FastTrainClient ${SOURCE_FILES})

target_link_libraries(FastTrainClient Utils)
target_include_directories(FastTrainClient PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)

qt5_use_modules(FastTrainClient Core Widgets Gui Location)