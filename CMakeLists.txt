cmake_minimum_required(VERSION 3.8)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 17)
set(HEADER_FOLDER ./include)
set(SOURCE_FILES src/main.cpp src/Ingester.cpp src/RulesEngine.cpp)

include_directories(${HEADER_FOLDER})
add_executable(GeneticAlgorithm
        ${SOURCE_FILES}
        ${HEADER_FOLDER}/config.h
        ${HEADER_FOLDER}/Ingester.h
        ${HEADER_FOLDER}/Population.h
        ${HEADER_FOLDER}/utils.h
        ${HEADER_FOLDER}/Individual.h)
