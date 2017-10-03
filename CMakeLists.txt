cmake_minimum_required(VERSION 3.8)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Individual.cpp Individual.h Population.cpp Population.h randomUtil.h config.h)
add_executable(GeneticAlgorithm ${SOURCE_FILES})