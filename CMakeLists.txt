cmake_minimum_required(VERSION 3.14)

project(SimplePicCut VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets Gui REQUIRED)


include_directories(src/)
include_directories(src/include)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SimplePicCut
        MANUAL_FINALIZATION
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET SimplePicCut APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(SimplePicCut SHARED)
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(SimplePicCut)
    endif()
endif()

add_subdirectory(src)

target_link_libraries(SimplePicCut PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SimplePicCut)
endif()
