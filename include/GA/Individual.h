#ifndef GENETICALGORITHM_INDIVIDUAL_H
#define GENETICALGORITHM_INDIVIDUAL_H

#include <stdint-gcc.h>
#include "utils.h"
#include "RulesEngine.h"
#include "Ingester.h"
#include <cmath>
#include <iostream>

namespace GA {

    enum fitnessStrategy { COUNTING_ONES, SQUARED, RULES };

    template <typename fitnessType = int>
    class Individual {

    public:

        Individual(int size, fitnessStrategy strategy, Config* conf) {
            this->chromosome = new float[size];
            this->fitnessStrat = strategy;
            this->size = size;
            this->conf = conf;
            for (int i = 0; i < size; i++) {
                // If it's the last bit, ensure it is not a wildcard
                if ((i + 1) % (conf->DATA_LENGTH * 2 + 1) == 0) {
                    this->chromosome[i] = getRandomNumber(0, 1);
                } else {
                    this->chromosome[i] = ((float) rand() / (RAND_MAX));
                }
            }
        }

        void toString(bool showChromosome) {
            std::cout << "Chromosome";
            if (showChromosome) {
                for (int i = 0; i < this->size; i++) {
                    std::cout << " " << this->chromosome[i];
                }
            }
        }

        int getFitness(data* dataIn) {
            return this->fitness;
        }

        void crossover(Individual<fitnessType>* partner) {
            int point = getRandomNumber(0, conf->NUMBER_OF_CHROMOSOMES - 1);
            auto partnerChromosomes = partner->getChromosomes();
            for (int i = point; i < this->size; i++) {
                float tempBit = this->chromosome[i];
                this->chromosome[i] = partnerChromosomes[i];
                partnerChromosomes[i] = tempBit;
            }
            partner->setChromosomes(partnerChromosomes);
        }

        // todo pass this like fitness func
        void mutate() {
            for (int i = 0; i < conf->NUMBER_OF_CHROMOSOMES; i++) {
                if (getRandomNumber(1, 1000) <= conf->PROBABILITY_OF_MUTATION) {
                    if ((i + 1) % (conf->DATA_LENGTH * 2 + 1) == 0) {
                        this->chromosome[i] = 1 - this->chromosome[i];
                    } else {
                        float randomChange = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.1));

                        if (getRandomNumber(0, 1) == 0) {
                            this->chromosome[i] -= randomChange;
                        } else {
                            this->chromosome[i] += randomChange;
                        }

                        if (this->chromosome[i] > 1) {
                            this->chromosome[i] = 1;
                        } else if (this->chromosome[i] < 0) {
                            this->chromosome[i] = 0;
                        }
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

        void setFitness(int fitness) { // change with fitnessType
            this->fitness = fitness;
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

        float* chromosome;
        int size;
        fitnessType fitness;
        fitnessStrategy fitnessStrat;
        Config* conf;
    };

}


#endif //GENETICALGORITHM_INDIVIDUAL_H
