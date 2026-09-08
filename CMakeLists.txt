cmake_minimum_required(VERSION 3.5)
project(FileSearchEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(search
    src/main.cpp
    src/FileCrawler.cpp
    src/Tokenizer.cpp
    src/DocumentManager.cpp
    src/InvertedIndex.cpp
    src/SearchEngine.cpp
)
