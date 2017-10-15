#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdint-gcc.h>
#include "randomUtil.h"
#include "config.h"
#include <cmath>
#include <iostream>

enum fitnessStrategy { COUNTING_ONES, SQUARED };

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
        for (int i = 0; i < this->size; i++) {
            std::cout << unsigned(this->chromosome[i]);
        }
        std::cout << " with fitness " << this->getFitness();
    }

    int getFitness() {
        switch (this->fitnessStrat) {
            case (COUNTING_ONES):
                return this->getFitnessCountingOnes();
            case (SQUARED):
                return this->getFitnessSquared();
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

    int* chromosome;
    int size;
    fitnessType fitness;
    fitnessStrategy fitnessStrat;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
