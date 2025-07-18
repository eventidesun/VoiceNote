#ifndef AISUMMARIZER_H
#define AISUMMARIZER_H

#include "LLMInference.h"
#include <string>

class AISummarizer {
public:
    AISummarizer(const std::string& modelPath);
    bool summarizeFile(const std::string& inputFilePath, const std::string& outputFilePath);
    std::string getSummary() const;

private:
    std::unique_ptr<LLMInference> _llm;
    std::string _summary;
};

#endif
