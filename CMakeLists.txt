cmake_minimum_required(VERSION 3.10)
project(group08)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt5 REQUIRED COMPONENTS Widgets Multimedia MultimediaWidgets Network)

# Qt setup
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include dirs
include_directories(
        editor_class
        storage_class
#        AI_Summarizer/src/llm
)

# Summarizer executable
#add_executable(xxxxxx
#        AI_Summarizer/src/llm/AISummarizer.cpp
#        AI_Summarizer/src/llm/LLMInference.cpp
#)

# --- Google Test Setup ---
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# --- Backend Executable (no main here, just for building shared code) ---
add_library(group08_backend
        editor_class/editor.cpp
        storage_class/storage.cpp
)
target_include_directories(group08_backend PUBLIC
        editor_class
        storage_class
)

# --- Unit Tests ---

# Storage Tests
add_executable(storage_tests
        tests/test_main.cpp
        tests/storage_test.cpp
)

include(GoogleTest)

target_link_libraries(storage_tests group08_backend gtest)
gtest_discover_tests(storage_tests)

# Editor Tests
add_executable(editor_tests
        tests/test_main.cpp
        tests/editor_test.cpp
)
target_link_libraries(editor_tests group08_backend gtest)
gtest_discover_tests(editor_tests)

# --- Qt App ---

# This assumes your Qt .cpp and .ui files are in SpeechToText/
add_subdirectory(SpeechToText)
add_subdirectory(individual_recording_page)
add_subdirectory(manage_recording_page)
add_subdirectory(whisper.cpp)
add_subdirectory(AI_Summarizer/llama.cpp)


# --- Final App Executable (Entry Point) ---
add_executable(group08_app
        main.cpp
)

target_link_libraries(group08_app
        Qt5::Widgets
        group08_backend
        speechtotext_lib
        individual_recording_page_lib
        manage_recording_page_lib
        llama
        ggml
        ${CMAKE_SOURCE_DIR}/build/Desktop-Debug/whisper.cpp/libwhisper_lib.a
)