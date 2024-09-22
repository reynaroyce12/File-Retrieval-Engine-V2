cmake_minimum_required(VERSION 3.22)

project(file-retrieval-engine
        VERSION 1.0
        DESCRIPTION "C++ File Retrieval Engine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(file-retrieval-engine
               src/file-retrieval-engine.cpp
               src/AppInterface.cpp
               src/ProcessingEngine.cpp
               src/IndexStore.cpp)

target_include_directories(file-retrieval-engine PUBLIC include)