//
// Created by arthur on 17/10/17.
//

#ifndef GENETICALGORITHM_RULESENGINE_H
#define GENETICALGORITHM_RULESENGINE_H

#include "Ingester.h"

typedef struct {
    int* condition;
    int size;
    int output;
} rule;


class RulesEngine {

public:

    rule* generateRuleBase(int* chromosome);
//    int checkRules(data* dataIn, int* chromosome); // Should i forward declare data ?
    int checkRules(data* dataIn, rule* rulesBase); // Should i forward declare data ?

private:

    bool isEqual(int* a, int* b, int size);
};


#endif //GENETICALGORITHM_RULESENGINE_H
