#ifndef GENETICALGORITHM_CONFIG_H
#define GENETICALGORITHM_CONFIG_H

namespace GA {

    class Config {
    public:
        Config(int gens, int chromosomes, int pop, int xover, int mutate, int tournament, int folds, int dataLength,
               int numData, std::string resultsFile = "", bool timestampFile = false)
        {
            this->NUMBER_OF_GENERATIONS = gens;
            this->NUMBER_OF_CHROMOSOMES = chromosomes;
            this->SIZE_OF_POPULATION = pop;
            this->PROBABILITY_OF_CROSSOVER = xover;
            this->PROBABILITY_OF_MUTATION = mutate;
            this->TOURNAMENT_SIZE = tournament;
            this->NUMBER_OF_FOLDS = folds;
            this->DATA_LENGTH = dataLength;
            this->NUMBER_OF_DATA = numData;
            this->resultsFile = resultsFile;
            this->timestampFile = timestampFile;
        }

        int NUMBER_OF_GENERATIONS;
        int NUMBER_OF_CHROMOSOMES;
        int SIZE_OF_POPULATION;
        int PROBABILITY_OF_CROSSOVER;
        int PROBABILITY_OF_MUTATION;
        int TOURNAMENT_SIZE;
        int NUMBER_OF_FOLDS;
        int DATA_LENGTH;
        int NUMBER_OF_DATA;
        std::string resultsFile;
        bool timestampFile;
    };

}


#endif //GENETICALGORITHM_CONFIG_H
