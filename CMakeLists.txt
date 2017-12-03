cmake_minimum_required(VERSION 3.8)

project(EvolvingRuleInductionSystem VERSION 1.4.0)

set(CMAKE_CXX_STANDARD 11)

set(HEADER_DIR ./include)

set(SOURCE_DIR ./src)

set(GA_HEADER_DIR ./include/GA)

set(SOURCE_FILES
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/Ingester.cpp
        ${SOURCE_DIR}/RulesEngine.cpp
        ${HEADER_DIR}/IEvaluation.h
        ${HEADER_DIR}/FPRuleEvaluation.h)

set(GA_SOURCE_FILES
        ${GA_HEADER_DIR}/Population.h
        ${GA_HEADER_DIR}/utils.h
        ${GA_HEADER_DIR}/Individual.h
        ${GA_HEADER_DIR}/Config.h
        ${GA_HEADER_DIR}/Environment.h)

include_directories(${HEADER_DIR})

add_executable(eris
        ${SOURCE_FILES}
        ${GA_SOURCE_FILES})
