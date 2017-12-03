#ifndef EVOLVINGRULEINDUCTIONSYSTEM_RULEMUTATOR_H
#define EVOLVINGRULEINDUCTIONSYSTEM_RULEMUTATOR_H

#include <GA/IMutatable.h>
#include <GA/Config.h>

template <typename fitnessType>
class RuleMutator: public GA::IMutatable<fitnessType> {

public:

    void mutate(GA::Individual<fitnessType>* individual, GA::Config* conf) {
        auto chromosomes = individual->getChromosomes();
        for (int i = 0; i < conf->NUMBER_OF_CHROMOSOMES; i++) {
            if (getRandomNumber(1, 1000) <= conf->PROBABILITY_OF_MUTATION) {
                if ((i + 1) % (conf->DATA_LENGTH * 2 + 1) == 0) {
                    chromosomes[i] = 1 - chromosomes[i];
                } else {
                    float randomChange = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.1));

                    if (getRandomNumber(0, 1) == 0) {
                        chromosomes[i] -= randomChange;
                    } else {
                        chromosomes[i] += randomChange;
                    }

                    if (chromosomes[i] > 1) {
                        chromosomes[i] = 1;
                    } else if (chromosomes[i] < 0) {
                        chromosomes[i] = 0;
                    }
                }
            }
        }
    }

};


#endif //EVOLVINGRULEINDUCTIONSYSTEM_RULEMUTATOR_H
