#include "ProcessingEngine.hpp"

ProcessingEngine::ProcessingEngine(std::shared_ptr<IndexStore> store) : store(store) { }

IndexResult ProcessingEngine::indexFolder(std::string folderPath) {
    IndexResult result = {0.0, 0};
    // TO-DO get the start time
    // TO-DO crawl the folder path and extrac all file paths
    // TO-DO for each file put the document path in the index store and retrieve the document number
    // TO-DO for each file extract all alphanumeric terms that are larger than 2 characters and count their frequencies
    // TO-DO increment the total number of read bytes
    // TO-DO update the main index with the word frequencies for each document
    // TO-DO get the stop time and calculate the execution time
    // TO-DO return the execution time and the total number of bytes read

    return result;
}

SearchResult ProcessingEngine::search(std::vector<std::string> terms) {
    SearchResult result = {0.0, { }};
    // TO-DO get the start time
    // TO-DO for each term get the pairs of documents and frequencies from the index store
    // TO-DO combine the returned documents and frequencies from all of the specified terms
    // TO-DO sort the document and frequency pairs and keep only the top 10
    // TO-DO for each document number get from the index store the document path
    // TO-DO get the stop time and calculate the execution time
    // TO-DO return the execution time and the top 10 documents and frequencies

    return std::move(result);
}