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

    rule* generateRuleBase(float* chromosome);
    int checkRules(data* dataIn, rule* rulesBase); // Should i forward declare data ?

private:

    bool isEqual(float* a, float* b, int size);
};


#endif //GENETICALGORITHM_RULESENGINE_H
