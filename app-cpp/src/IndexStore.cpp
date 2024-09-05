#include "IndexStore.hpp"

IndexStore::IndexStore() {
    // TO-DO initialize the DocumentMap and TermInvertedIndex members
}

long IndexStore::putDocument(std::string documentPath) {
    long documentNumber = 0;
    // TO-DO assign a unique number to the document path and return the number

    return documentNumber;
}

std::string IndexStore::getDocument(long documentNumber) {
    std::string documentPath = "";
    // TO-DO retrieve the document path that has the given document number

    return documentPath;
}

void IndexStore::updateIndex(long documentNumber, const std::unordered_map<std::string, long> &wordFrequencies) {
    // TO-DO update the TermInvertedIndex with the word frequencies of the specified document
}

std::vector<DocFreqPair> IndexStore::lookupIndex(std::string term) {
    std::vector<DocFreqPair> results = {};
    // TO-DO return the document and frequency pairs for the specified term

    return std::move(results);
}
