#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdint-gcc.h>
#include "randomUtil.h"
#include "config.h"
#include "RulesEngine.h"
#include "Ingester.h"
#include <cmath>
#include <iostream>

enum fitnessStrategy { COUNTING_ONES, SQUARED, RULES };


template <typename fitnessType = int>
class Individual {

public:

    Individual(int size, fitnessStrategy strategy) {
        this->chromosome = new int[size];
        this->fitnessStrat = strategy;
        this->size = size;
        for (int i = 0; i < size; i++) {
            this->chromosome[i] = getRandomNumber(0, 1);
        }
    }

    void toString() {
        std::cout << "Chromosome ";
//        for (int i = 0; i < this->size; i++) {
//            std::cout << unsigned(this->chromosome[i]);
//        }
        std::cout << " with fitness " << this->getFitness();
    }

    int getFitness() {
        switch (this->fitnessStrat) {
            case (COUNTING_ONES):
                return this->getFitnessCountingOnes();
            case (SQUARED):
                return this->getFitnessSquared();
            case (RULES):
                return this->getFitnessRules();
            default:
                std::cout << "Please choose an appropriate fitness strategy"; return 0;
        }
    }

    void crossover(Individual<fitnessType>* partner) {
        int point = getRandomNumber(0, NUMBER_OF_CHROMOSONES);
        auto partnerChromosomes = partner->getChromosomes();
        int tempBit;
        for (int i = point; i < this->size; i++) {
            tempBit = this->chromosome[i];
            this->chromosome[i] = partnerChromosomes[i];
            partnerChromosomes[i] = tempBit;
        }
        partner->setChromosomes(partnerChromosomes);
    }

    void mutate() {
        int point = getRandomNumber(0, NUMBER_OF_CHROMOSONES);
        this->chromosome[point] = 1 - this->chromosome[point];
    }

    int getSize() {
        return this->size;
    }

    int* getChromosomes() {
        return this->chromosome;
    }

    int* setChromosomes(int* chromosome) {
        this->chromosome = chromosome;
    }

    fitnessStrategy getFitnessStrategy() {
        return this->fitnessStrat;
    }

private:

    int getFitnessSquared() {
        this->fitness = 0;
        for (int i = 0; i < this->size; i++) {
            if (this->chromosome[this->size - i - 1] == 1) {
                this->fitness += pow(2, i);
            }
        }
        return this->fitness;
    }

    int getFitnessCountingOnes() {
        this->fitness = 0;
        for (int i = 0; i < this->size; i++) {
            if (this->chromosome[i] == 1) {
                this->fitness++;
            }
        }
        return this->fitness;
    }

    int getFitnessRules() {
        // Generate a rule base on the individuals chromosomes
        auto rulesEngine = new RulesEngine();
        auto ruleBase = rulesEngine->generateRuleBase(this->chromosome);
//        for (int i = 0; i < NUM_RULES; i++) {
//            std::cout << "Condition";
//            for (int j = 0; j < ruleBase[i].size; j++) {
//                std::cout << ruleBase[i].condition[j];
//            }
//            std::cout << " " << ruleBase[i].output;
//            std::cout << "\n";
//        }

        auto ingester = new Ingester();
        auto dataIn = ingester->readFile("../data/data1.txt");

        this->fitness = rulesEngine->checkRules(dataIn, this->chromosome);
        return this->fitness;
    }

    int* chromosome;
    int size;
    fitnessType fitness;
    fitnessStrategy fitnessStrat;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
