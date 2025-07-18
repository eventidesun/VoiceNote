#include "AISummarizer.h"
#include <fstream>
#include <sstream>
#include <iostream>

AISummarizer::AISummarizer(const std::string& modelPath) {
    float temperature = 1.0f;
    float minP = 0.05f;
    _llm = std::make_unique<LLMInference>();
    _llm->loadModel(modelPath, minP, temperature);
    _llm->addChatMessage("You are a helpful assistant.", "system");
}

bool AISummarizer::summarizeFile(const std::string& inputFilePath, const std::string& outputFilePath) {
    // test if inputfile is valid
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
        return false;
    }

    // read inputfile
    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    std::string textToSummarize = buffer.str();
    inputFile.close();

    // run inference
    std::string query = "Please summarize the following text into notes and extract key points:\n\n" + textToSummarize;
    _llm->startCompletion(query);

    std::string predicted;
    _summary.clear();
    while ((predicted = _llm->completionLoop()) != "[EOG]") {
        _summary += predicted;
    }
    _llm->stopCompletion();

    // write to output
    std::ofstream outputFile(outputFilePath);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        return false;
    }
    outputFile << _summary;
    outputFile.close();

    return true;
}

std::string AISummarizer::getSummary() const {
    return _summary;
}
