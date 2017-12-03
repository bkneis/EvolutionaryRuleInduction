#ifndef GENETICALGORITHM_EVALUATION_H
#define GENETICALGORITHM_EVALUATION_H

#include <Individual.h>

/**
 * Interface for evaluation object to implement to be passed to the GA environment
 * @tparam fitnessType
 */
template <typename fitnessType>
class IEvaluation {

public:
    virtual int calculateFitness(Individual<fitnessType>* individual, data* dataIn) = 0;

};


#endif //GENETICALGORITHM_EVALUATION_H
