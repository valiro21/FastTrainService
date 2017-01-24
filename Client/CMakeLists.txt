project(FastTrainService)

include_directories(..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lneo4j-client -lssl -lcrypto")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Location REQUIRED )

qt5_wrap_cpp(FastTrainClientWrap CitySelector.hpp)
qt5_wrap_cpp(FastTrainClientWrap ActionSelector.hpp)
qt5_wrap_cpp(FastTrainClientWrap SearchButton.hpp)

set(SOURCE_FILES
        ${SOURCE_FILES} main.cpp
        DateSelector.cpp
        DateSelector.hpp
        CitySelector.cpp
        ${FastTrainClientWrap}
        ActionSelector.cpp
        SearchWidget.cpp
        Client.cpp
        SearchButton.cpp
        InformationPanel.cpp)

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_executable(FastTrainClient ${SOURCE_FILES})

target_link_libraries(FastTrainClient Utils)
target_include_directories(FastTrainClient PUBLIC $<TARGET_PROPERTY:Utils,INCLUDE_DIRECTORIES>)

qt5_use_modules(FastTrainClient Core Widgets Gui Location)