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

if(WIN32)
    # For MSVC, enable UTF-8 codec
       add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
       add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
       add_executable(SimplePicCut WIN32)
endif()


add_subdirectory(src)

target_link_libraries(SimplePicCut PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SimplePicCut)
endif()
