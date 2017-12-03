#ifndef GENETICALGORITHM_RULESENGINE_H
#define GENETICALGORITHM_RULESENGINE_H

#include "Ingester.h"

typedef struct {
    float* condition;
    int size;
    int output;
} rule;


class RulesEngine {

public:
    RulesEngine(int numRules, int dataLength) {
        this->NUM_RULES = numRules;
        this->DATA_LENGTH = dataLength;
    }
    rule* generateRuleBase(float* chromosome);
    int checkRules(data* dataIn, rule* rulesBase, int numData);

private:
    int NUM_RULES;
    int DATA_LENGTH;

    bool isEqual(float* a, float* b, int size);
};


#endif //GENETICALGORITHM_RULESENGINE_H
