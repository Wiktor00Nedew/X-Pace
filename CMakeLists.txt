cmake_minimum_required(VERSION 3.22)
project(X_Pace)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

include_directories(include)

if(WIN32)
    set(CMAKE_PREFIX_PATH libraries/win32/lib/cmake)
endif(WIN32)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(X_Pace main.cpp src/windows/MainWindow.cpp)

target_compile_options(X_Pace PRIVATE -Wall)

target_link_libraries(X_Pace
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )