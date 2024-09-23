#ifndef PROCESSING_ENGINE_H
#define PROCESSING_ENGINE_H

#include <memory>
#include <string>
#include <vector>

#include "IndexStore.hpp"

struct IndexResult {
    double executionTime;
    long totalBytesRead;
};

struct DocPathFreqPair {
    std::string documentPath;
    long wordFrequency;
};

struct SearchResult {
    double excutionTime;
    std::vector<DocPathFreqPair> documentFrequencies;
};

class ProcessingEngine {
    // keep a reference to the index store
    std::shared_ptr<IndexStore> store;

    public:
        // constructor
        ProcessingEngine(std::shared_ptr<IndexStore> store);

        // default virtual destructor
        virtual ~ProcessingEngine() = default;

        IndexResult indexFolder(std::string folderPath);
        SearchResult search(std::vector<std::string> terms);

    private:
        std::unordered_map<std::string, long> extractWords(const std::string& fileContent);
        std::vector<DocPathFreqPair> searchAndSort(std::vector<std::string> terms);
};

#endif