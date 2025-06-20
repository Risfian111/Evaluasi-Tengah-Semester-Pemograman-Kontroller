cmake_minimum_required(VERSION 3.5)

project(QtMonitoring)

set(CMAKE_CXX_STANDARD 11)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

set(SOURCES
    main.cpp
    mainwindow.cpp
)

set(HEADERS
    mainwindow.h
)

set(UIS
    mainwindow.ui
)

qt5_wrap_ui(UI_HEADERS ${UIS})

add_executable(QtMonitoring ${SOURCES} ${HEADERS} ${UI_HEADERS})

target_link_libraries(QtMonitoring Qt5::Widgets)
