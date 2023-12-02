cmake_minimum_required(VERSION 3.26)
project(Airline_Processing)

set(CMAKE_CXX_STANDARD 14)

add_executable(Airline_Processing Processor.cpp SplayTree.cpp
        Processor.h)