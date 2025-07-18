set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

add_library(individual_recording_page_lib
        individualrecordingpage.cpp
        individualrecordingpage.h
        individualrecordingpage.ui
        ../../AI_Summarizer/src/llm/AISummarizer.cpp
        ../../AI_Summarizer/src/llm/LLMInference.cpp
)

target_include_directories(individual_recording_page_lib PRIVATE
        ${Qt5Widgets_INCLUDE_DIRS}
        ../../AI_Summarizer/src
        ../../AI_Summarizer/llama.cpp
        ../../AI_Summarizer/llama.cpp/include
        ../../AI_Summarizer/llama.cpp/common
        ../editor_class
        ../storage_class
)

target_link_libraries(individual_recording_page_lib
        Qt5::Widgets
        llama
        ggml
#        common
        group08_backend
)
