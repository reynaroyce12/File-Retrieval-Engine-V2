#ifndef APP_INTERFACE_H
#define APP_INTERFACE_H

#include <memory>

#include "ProcessingEngine.hpp"

class AppInterface {
    // keep a reference to the processing engine
    std::shared_ptr<ProcessingEngine> engine;

    public:
        // constructor
        AppInterface(std::shared_ptr<ProcessingEngine> engine);

        // default virtual destructor
        virtual ~AppInterface() = default;

        // read commands from the CLI
        void readCommands();
};

#endif