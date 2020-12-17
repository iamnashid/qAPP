cmake_minimum_required(VERSION 3.9)
project(qAPP VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(qAPP
        audio_stream.cpp
        audio_stream.h
        interfaces.cpp
        interfaces.h
        json.hpp
        main.cpp
        parser.cpp
        parser.h
        translations.h)

target_link_libraries(qAPP Qt5::Widgets mpg123 ao curl)