#include "IndexStore.hpp"

#include <algorithm>
#include <iostream>
#include <string>

IndexStore::IndexStore()
{
    documentMap = {};
    reverseDocumentMap = {};
    termInvertedIndex = {};
}

long IndexStore::putDocument(std::string documentPath)
{
    // CHANGE FOR MULTITHREADING  IMPORTANT! you need to make sure that only one thread at a time can access this method
    std::lock_guard<std::mutex> lock(documentMapMutex);

    if (documentMap.contains(documentPath)) {
        return documentMap[documentPath];
    }

    long documentNumber = documentMap.size() + 1;
    documentMap[documentPath] = documentNumber;

    // reverse map for getDocument method for constant complexity while retrieving docs
    reverseDocumentMap[documentNumber] = documentPath;

    return documentNumber;
}

std::string IndexStore::getDocument(long documentNumber)
{
    std::string documentPath = "";

    if (reverseDocumentMap.contains(documentNumber)) {
        documentPath = reverseDocumentMap[documentNumber];
    }

    return documentPath;
}

void IndexStore::updateIndex(long documentNumber, const std::unordered_map<std::string, long> &wordFrequencies)
{
    // CHANGE FOR MULTITHREADING  IMPORTANT! you need to make sure that only one thread at a time can access this method
    std::lock_guard<std::mutex> lock(termInvertedIndexMutex);

    for (const auto &wordFrequency : wordFrequencies) {
        std::string word = wordFrequency.first;
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        long frequency = wordFrequency.second;

        auto itr = termInvertedIndex.find(word);
        if (itr != termInvertedIndex.end()) {
            itr->second.push_back({documentNumber, frequency});
        }
        else{
            termInvertedIndex[word] = {{documentNumber, frequency}};
        }
    }
}

std::vector<DocFreqPair> IndexStore::lookupIndex(std::string term)
{
    std::vector<DocFreqPair> results = {};
    if (termInvertedIndex.contains(term)) {
        results = termInvertedIndex[term];
    }

    return std::move(results);
}
