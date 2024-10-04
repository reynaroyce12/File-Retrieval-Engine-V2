#include "ProcessingEngine.hpp"

#include <chrono>
#include <fstream>
#include <filesystem>
#include <iostream>

ProcessingEngine::ProcessingEngine(std::shared_ptr<IndexStore> store, int numWorkerThreads) :
        store(store), numWorkerThreads(numWorkerThreads) { }


// Utility function for extracting terms for indexing
std::unordered_map<std::string, long> ProcessingEngine::extractWords(const std::string& fileContent) {
    std::unordered_map<std::string, long> wordFrequency;
    std::string currentWord;

    for (char charecter : fileContent) {
        if (std::isalnum(charecter)) {
            currentWord += charecter;
        } else {
            if (currentWord.length() > 2) {
                wordFrequency[currentWord]++;
            }
            currentWord.clear();
        }
    }

    if(currentWord.length() > 2) {
        wordFrequency[currentWord]++;
    }
    return wordFrequency;
}

// Utility function for search and sort operations
std::vector<DocPathFreqPair> ProcessingEngine::searchAndSort(std::vector<std::string> terms)
{
    bool hasAnd = false;
    
    auto andPos = std::find(terms.begin(), terms.end(), "AND");
    if (andPos != terms.end()) {
        hasAnd = true;
        terms.erase(andPos);  
    }

    // For storing documents and their total frequencies across terms
    std::unordered_map<long, long> combinedResults;  

    // Process each term and accumulate frequencies for matching documents
    for (const auto &term : terms) {
        if (term.empty()) continue;

        auto termResults = store->lookupIndex(term);

        if (termResults.empty()) {
            return {};
        }

        if (combinedResults.empty()) {
            // If this is the first term, add all its results to combinedResults
            for (const auto &result : termResults) {
                combinedResults[result.documentNumber] = result.wordFrequency;
            }
        } else {
            // If not the first term, update frequencies for documents already in combinedResults
            std::unordered_map<long, long> currentResults;
            for (const auto &result : termResults) {
                if (combinedResults.count(result.documentNumber)) {
                    currentResults[result.documentNumber] = combinedResults[result.documentNumber] + result.wordFrequency;
                }
            }
            combinedResults = std::move(currentResults); 
        }
    }

    if (hasAnd && combinedResults.empty()) {
        return {};
    }

    std::vector<DocPathFreqPair> sortedResults;
    for (const auto &[documentNumber, frequency] : combinedResults) {
        std::string documentPath = store->getDocument(documentNumber);
        sortedResults.push_back({documentPath, frequency});
    }

    // Sort by frequency in descending order
    std::sort(sortedResults.begin(), sortedResults.end(), [](const DocPathFreqPair &value1, const DocPathFreqPair &value2) {
        return value1.wordFrequency > value2.wordFrequency;
    });

    // Return top 10 results
    if (sortedResults.size() > 10) {
        sortedResults.resize(10);
    }

    return sortedResults;
}

IndexResult ProcessingEngine::indexFolder(std::string folderPath) {

    IndexResult result = {0.0, 0};

    std::queue<std::string> fileQueue;
    std::mutex fileQueueMutex;
    std::condition_variable cv;
    std::vector<std::thread> threads;
    bool isDone = false;

    auto indexingStartTime = std::chrono::steady_clock::now();

    for (const auto& file : std::filesystem::recursive_directory_iterator(folderPath)) {
        if (file.is_regular_file()) {
            std::lock_guard<std::mutex> lock(fileQueueMutex);
            fileQueue.push(file.path().string());
        }
    }

    auto worker = [&]() {

        while (true) {
            std::string filePath;

            {
                std::unique_lock<std::mutex> lock(fileQueueMutex);

                // In sleep state until either of the condition is met
                cv.wait(lock, [&]() {
                    return !fileQueue.empty() || isDone; 
                });

                if (fileQueue.empty()) {
                    if (isDone) return;
                    continue;
                }

                filePath = fileQueue.front();
                fileQueue.pop();
            }

            if(!filePath.empty()) {
                long documentNumber = store->putDocument(filePath);
                std::ifstream file(filePath);
                if (!file) {
                    std::cerr << "Cannot open the file: " << filePath << std::endl;
                    continue;
                }

                std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                auto wordFrequency = extractWords(content);
                {
                    std::lock_guard<std::mutex> lock(fileQueueMutex);
                    result.totalBytesRead += content.size();
                }
                store->updateIndex(documentNumber, wordFrequency);
            }
        }
    };

    for (int i = 0; i < numWorkerThreads; i++) {
        threads.emplace_back(worker);
    }

    {
        std::lock_guard<std::mutex> lock(fileQueueMutex);
        isDone = true;
    }
    cv.notify_all();

    for(auto& thread : threads) {
        thread.join();
    }

    auto indexingStopTime = std::chrono::steady_clock::now();
    result.executionTime = std::chrono::duration_cast<std::chrono::seconds>(indexingStopTime - indexingStartTime).count();
    
    return result;
}

SearchResult ProcessingEngine::search(std::vector<std::string> terms) {

    SearchResult result = {0.0, { }};

    auto searchStartTime = std::chrono::steady_clock::now();

    bool isAndQuery = (std::find(terms.begin(), terms.end(), "AND") != terms.end());

    if (isAndQuery) {
        terms.erase(terms.begin() + 1);
    } else if(terms.size() == 1) {
        terms.push_back("");
    }
 
    result.documentFrequencies  = searchAndSort(terms);

    auto searchStopTime = std::chrono::steady_clock::now();

    auto durationInSeconds = std::chrono::duration_cast<std::chrono::seconds>(searchStopTime - searchStartTime).count();
    result.excutionTime = durationInSeconds; 
    

    return std::move(result);
}
