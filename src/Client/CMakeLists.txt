project(FastTrainService)

include_directories(${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -lneo4j-client -lssl -lcrypto")

find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Location REQUIRED )

qt5_wrap_cpp(FastTrainClientWrap CitySelector.hpp)
qt5_wrap_cpp(FastTrainClientWrap ActionSelector.hpp)
qt5_wrap_cpp(FastTrainClientWrap SearchButton.hpp)
qt5_wrap_cpp(FastTrainClientWrap DateWidget.hpp)

set(SOURCE_FILES
        ${SOURCE_FILES} main.cpp DateSelector.cpp DateSelector.hpp CitySelector.cpp ${FastTrainClientWrap} Calendar.cpp Calendar.hpp ActionSelector.cpp ActionSelector.hpp SearchWidget.cpp SearchWidget.hpp Client.cpp Client.hpp SearchButton.cpp DateWidget.cpp HourWidget.cpp HourWidget.hpp)

set(EXECUTABLE_OUTPUT_PATH ../../bin/${CMAKE_BUILD_TYPE})

add_executable(FastTrainClient ${SOURCE_FILES})

qt5_use_modules( FastTrainClient Core Widgets Gui Location)