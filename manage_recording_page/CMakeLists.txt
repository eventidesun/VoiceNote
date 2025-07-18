cmake_minimum_required(VERSION 3.10)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets Network REQUIRED)

add_library(manage_recording_page_lib
        managerecordingpage.cpp
        managerecordingpage.h
        managerecordingpage.ui
)

target_link_libraries(manage_recording_page_lib
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        Qt5::Network
        group08_backend
        speechtotext_lib
        individual_recording_page_lib
)
