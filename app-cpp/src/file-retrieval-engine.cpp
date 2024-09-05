#include <iostream>

#include "IndexStore.hpp"
#include "ProcessingEngine.hpp"
#include "AppInterface.hpp"

int main(int argc, char** argv)
{
    std::shared_ptr<IndexStore> store = std::make_shared<IndexStore>();
    std::shared_ptr<ProcessingEngine> engine = std::make_shared<ProcessingEngine>(store);
    std::shared_ptr<AppInterface> interface = std::make_shared<AppInterface>(engine);

    interface->readCommands();

    return 0;
}