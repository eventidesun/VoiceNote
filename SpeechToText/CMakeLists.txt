# SpeechToText/CMakeLists.txt

# Build as a library to link into the main app
add_library(speechtotext_lib
        speechtotext.cpp
        speechtotext.h
        speechtotext.ui
)

# Link necessary Qt and backend libraries
target_link_libraries(speechtotext_lib PRIVATE
        Qt5::Widgets
        Qt5::Multimedia
        Qt5::MultimediaWidgets
        Qt5::Network
        group08_backend
)

# macOS-specific settings
if(APPLE)
    find_library(COREAUDIO CoreAudio)
    find_library(AVFOUNDATION AVFoundation)
    target_link_libraries(speechtotext_lib PRIVATE
            ${COREAUDIO}
            ${AVFOUNDATION}
    )

    set(CMAKE_INSTALL_RPATH "@executable_path/../Frameworks")
endif()
