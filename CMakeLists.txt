cmake_minimum_required(VERSION 3.8)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Individual.h Population.h randomUtil.h config.h Ingester.cpp Ingester.h RulesEngine.cpp RulesEngine.h)
add_executable(GeneticAlgorithm ${SOURCE_FILES})