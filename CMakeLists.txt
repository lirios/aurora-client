cmake_minimum_required(VERSION 3.10.0)

project("AuroraClient"
    VERSION "0.0.0"
    DESCRIPTION "Qt-style API for Wayland clients"
    LANGUAGES CXX C
)

## Shared macros and functions:
if(NOT LIRI_LOCAL_ECM)
    find_package(LiriCMakeShared "2.0.0" REQUIRED NO_MODULE)
    list(APPEND CMAKE_MODULE_PATH "${LCS_MODULE_PATH}")
endif()

## Add some paths to check for CMake modules:
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/cmake/3rdparty")

## Set minimum versions required:
set(QT_MIN_VERSION "5.15.0")

## Liri specific setup common for all modules:
include(LiriSetup)

## Only build on the appropriate platforms.
if(NOT (LINUX OR APPLE OR QNX))
    message(NOTICE "Skipping the build as the condition \"LINUX OR APPLE OR QNX\" is not met.")
    return()
endif()

## Find Qt 5:
find_package(Qt5 "${QT_MIN_VERSION}"
    CONFIG REQUIRED
    COMPONENTS
        Core
        Qml
        Quick
        Gui
        WaylandClient
)

## Add subdirectories:
add_subdirectory(src/client)
add_subdirectory(src/imports/client)
if(BUILD_TESTING)
    add_subdirectory(tests/auto/client)
endif()
