llama_add_compile_flags()

#
# libraries
#

# llama
file(GLOB COMMON_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../common/*.cpp")

add_library(llama
        ${COMMON_SRC}
        ../include/llama.h
        llama.cpp
        llama-adapter.cpp
        llama-arch.cpp
        llama-batch.cpp
        llama-chat.cpp
        llama-context.cpp
        llama-grammar.cpp
        llama-graph.cpp
        llama-hparams.cpp
        llama-impl.cpp
        llama-io.cpp
        llama-kv-cache.cpp
        llama-memory.cpp
        llama-mmap.cpp
        llama-model-loader.cpp
        llama-model.cpp
        llama-quant.cpp
        llama-sampling.cpp
        llama-vocab.cpp
        unicode-data.cpp
        unicode.cpp
        unicode.h
)

target_include_directories(llama PUBLIC . ../include ../common)
target_compile_features   (llama PUBLIC cxx_std_17) # don't bump

target_link_libraries(llama PUBLIC ggml)

if (BUILD_SHARED_LIBS)
    set_target_properties(llama PROPERTIES POSITION_INDEPENDENT_CODE ON)
    target_compile_definitions(llama PRIVATE LLAMA_BUILD)
    target_compile_definitions(llama PUBLIC  LLAMA_SHARED)
endif()
