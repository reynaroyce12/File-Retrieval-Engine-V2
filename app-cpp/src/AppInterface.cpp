#include "AppInterface.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>

AppInterface::AppInterface(std::shared_ptr<ProcessingEngine> engine) : engine(engine) { }

// Function for processing the search query for case insensitivity
std::string processSearchQuery(const std::string& searchQuery) {
    std::istringstream stream(searchQuery);
    std::string word;
    std::vector<std::string> processedWords;

    while (stream >> word) {
        if (word == "AND") {
            processedWords.push_back(word);
        } else {
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            processedWords.push_back(word);
        }
    }

    // Reconstructing the query
    std::string result;
    for (const auto& word : processedWords) {
        if (!result.empty()) {
            result += " "; 
        }
        result += word;
    }

    return result;
}

void AppInterface::readCommands() {
    
    // color code constants for output messages
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
    const std::string YELLOW = "\033[33m";
    const std::string RESET = "\033[0m";

    std::string command;

    while (true) {
        std::cout << "> <index | search | quit>  ";
        
        // read from command line
        std::getline(std::cin, command);

        // if the command is quit, terminate the program       
        if (command == "quit") {
            break;
        }

        if (command == "index") {
            std::cout << YELLOW << "Missing folder path for indexing!" << RESET << std::endl;
            continue;
        }

        if (command == "search") {
            std::cout << YELLOW << "Missing search terms!" << RESET << std::endl;
            continue;
        }
        
        // if the command begins with index, index the files from the specified directory
        if (command.size() >= 5 && command.substr(0, 5) == "index") {
            
            std::string folderPath = command.substr(6);

            if (!std::filesystem::exists(folderPath)) {
                std::cout << YELLOW << "Specified folder does not exist!" << RESET << std::endl;
                continue; 
            }

            folderPath.erase(0, folderPath.find_first_not_of(" "));
            folderPath.erase(folderPath.find_last_not_of(" ") + 1); 

            if (folderPath.empty()) {
                std::cout << YELLOW << "Missing folder path for indexing!" << RESET << std::endl;
                continue;
            }

            IndexResult result = engine->indexFolder(folderPath);

            if (result.totalBytesRead == 0) { 
                std::cout << YELLOW << "No files found to index!" << RESET << std::endl;
            } else {
                std::cout << GREEN << "Indexing completed with a total execution time of "
                          << result.executionTime << " seconds. Total bytes read: "
                          << result.totalBytesRead << RESET << std::endl;
            }

            continue;
        }

        // if the command begins with search, search for files that matches the query
        if (command.size() >= 6 && command.substr(0, 6) == "search") {
            std::string searchQuery = command.substr(7);
            std::string processedQuery = processSearchQuery(searchQuery);

            std::vector<std::string> terms;
            std::istringstream stream(processedQuery);
            std::string term;

            while (stream >> term) {
                terms.push_back(term);
            }

            SearchResult result = engine->search(terms);

            std::cout << "\nSearch executed in " << result.excutionTime << " μs." << std::endl;

            if (result.documentFrequencies.empty()) {
                std::cout << YELLOW << "No results found" << RESET << std::endl;
            } else {
                std::cout << "Search Results: " << "( Top 10 out of " << result.documentFrequencies.size() << ")\n"
                          << std::endl;
                for (const auto &docFrequency : result.documentFrequencies) {
                    std::cout << GREEN << docFrequency.documentPath << " (Frequency: " << docFrequency.wordFrequency << ")" << RESET << std::endl;
                }
            }

            continue;
        }

        std::cout << RED << "Unrecognized command! Please select an option from the menu!" << RESET << std::endl;
    }
}