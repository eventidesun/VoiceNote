#include "LLMInference.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) {
    std::string modelPath = "../models/Llama-3.2-1B-Instruct-Q4_K_S.gguf";
    std::string inputFilePath = "../transcription1.txt";
    std::string outputFilePath = "../summarized_transcription1.txt";

    // Step 1: Read text file
   
    std::ifstream inputFile(inputFilePath);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << inputFilePath << std::endl;
        return 1;
    }

    std::ostringstream buffer;
    buffer << inputFile.rdbuf();
    std::string textToSummarize = buffer.str();
    inputFile.close();

    // Query
    std::string query = "Please summarize the following text and extract key points for notes:\n\n" + textToSummarize;

    // Run Inference
    float temperature = 1.0f;
    float minP = 0.05f;
    std::unique_ptr<LLMInference> llmInference = std::make_unique<LLMInference>();
    llmInference->loadModel(modelPath, minP, temperature);
    llmInference->addChatMessage("You are a helpful assistant", "system");
    llmInference->startCompletion(query);

    std::string result;
    std::string predictedToken;
    while ((predictedToken = llmInference->completionLoop()) != "[EOG]") {
            result += predictedToken;            
    }
    std::cout << "\n\nSummary written to: " << outputFilePath << std::endl;
    
    // Step 4: Save output to file
    std::ofstream outputFile(outputFilePath);
    
    outputFile << result;
    outputFile.close();

    return 0;
}