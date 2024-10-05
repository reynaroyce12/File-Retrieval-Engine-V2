#include <iostream>
#include <string>

#include "IndexStore.hpp"
#include "ProcessingEngine.hpp"
#include "AppInterface.hpp"

int main(int argc, char** argv)
{   
    int numWorkerThreads = 0;

    if (argc > 1) {
        try {
            numWorkerThreads = std::stoi(argv[1]);

            if (numWorkerThreads < 0) {
                std::cerr << "Error: Negative number of worker threads provided. Exiting." << std::endl;
                return 1; 
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: Invalid worker thread count. Exiting." << std::endl;
            return 1; 
        }
    } else {
        std::cerr << "Error: No number of worker threads specified. Exiting." << std::endl;
        return 1; 
    }
    
    std::shared_ptr<IndexStore> store = std::make_shared<IndexStore>();
    std::shared_ptr<ProcessingEngine> engine = std::make_shared<ProcessingEngine>(store, numWorkerThreads);


    std::shared_ptr<AppInterface> interface = std::make_shared<AppInterface>(engine);

    interface->readCommands(numWorkerThreads);

    return 0;
}
