cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(
        archiver
        archiver.cpp
        argparser.cpp encoder.cpp huffman_coding.cpp symbol.cpp constants.h writer.cpp reader.cpp decoder.cpp trie.cpp text_exception.cpp)
