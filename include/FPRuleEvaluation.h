#ifndef GENETICALGORITHM_RULEEVALUATION_H
#define GENETICALGORITHM_RULEEVALUATION_H


#include <GA/Individual.h>
#include "GA/IEvaluation.h"

template <typename fitnessType>
class FPRuleEvaluation: public GA::IEvaluation<fitnessType> {

public:

    FPRuleEvaluation(RulesEngine* rulesEngine) {
        this->rulesEngine = rulesEngine;
    }

    int calculateFitness(GA::Individual<fitnessType>* individual, data* dataIn) override {
        auto rules = rulesEngine->generateRuleBase(individual->getChromosomes());
        return rulesEngine->checkRules(dataIn, rules, 1600);
    }

private:
    RulesEngine* rulesEngine;

};


#endif //GENETICALGORITHM_RULEEVALUATION_H
