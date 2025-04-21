cmake_minimum_required(VERSION 3.16)
project(edgeai-gui-app VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
include(GNUInstallDirs)

#find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Widgets Multimedia Quick)

find_package(PkgConfig REQUIRED)
pkg_search_module(gstreamer REQUIRED IMPORTED_TARGET gstreamer-1.0>=1.22)

add_compile_definitions(RT_BUILD=${RT_BUILD})

set(SOURCES
    main.cpp
    Backend.cpp
    Backend.h
)

qt_add_resources(RESOURCES
    qml.qrc
)

add_executable(edgeai-gui-app
    ${SOURCES}
    ${RESOURCES}
)
target_link_libraries(edgeai-gui-app PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Widgets
    Qt::Multimedia
    Qt::Quick
    PkgConfig::gstreamer
)

install(TARGETS edgeai-gui-app
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
