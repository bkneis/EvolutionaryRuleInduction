#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdint-gcc.h>
#include "utils.h"
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
        this->chromosome = new float[size];
        this->fitnessStrat = strategy;
        this->size = size;
        for (int i = 0; i < size; i++) {
            // If it's the last bit, ensure it is not a wildcard
            if ((i + 1) % (DATA_LENGTH + 1) == 0) {
                this->chromosome[i] = getRandomNumber(0, 1);
            } else {
                this->chromosome[i] = ((float) rand() / (RAND_MAX));
            }
        }
    }

    void toString(bool showChromosome = false) {
        std::cout << "Chromosome ";
        if (showChromosome) {
            for (int i = 0; i < this->size; i++) {
                std::cout << unsigned(this->chromosome[i]);
            }
        }
        std::cout << " with fitness " << this->getFitness() << "\n";
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
        int point = getRandomNumber(0, NUMBER_OF_CHROMOSOMES - 1);
        auto partnerChromosomes = partner->getChromosomes();
        for (int i = point; i < this->size; i++) {
            int tempBit = this->chromosome[i];
            this->chromosome[i] = partnerChromosomes[i];
            partnerChromosomes[i] = tempBit;
        }
        partner->setChromosomes(partnerChromosomes);
    }

    void mutate() {
        for (int i = 0; i < NUMBER_OF_CHROMOSOMES; i++) {
            if (getRandomNumber(1, 1000) <= PROBABILITY_OF_MUTATION) {
                if ((i + 1) % (DATA_LENGTH + 1) == 0) {
                    this->chromosome[i] = 1 - this->chromosome[i];
                } else {
                    this->chromosome[i] = ((float) rand() / (RAND_MAX));
                }
            }
        }
    }

    int getSize() {
        return this->size;
    }

    float* getChromosomes() {
        return this->chromosome;
    }

    void setChromosomes(float* chromosome) {
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

        auto ingester = new Ingester();
        auto dataIn = ingester->readFile(DATA_PATH);

        this->fitness = rulesEngine->checkRules(dataIn, ruleBase);
        return this->fitness;
    }

    float* chromosome;
    int size;
    fitnessType fitness;
    fitnessStrategy fitnessStrat;
};


#endif //GENETICALGORITHM_INDIVIDUAL_H
