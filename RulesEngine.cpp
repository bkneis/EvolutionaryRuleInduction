#include <iostream>
#include "RulesEngine.h"
#include "config.h"

rule *RulesEngine::generateRuleBase(int* chromosome) {
    auto ruleBase = new rule[NUM_RULES];
    int offset = 0;
    for(int i = 0; i < NUM_RULES; i++) {
        auto condition = new int[5];
        for (int j = 0; j < 5; j++) {
            condition[j] = chromosome[j + offset];
        }
        rule newRule = { condition, 5, chromosome[6 + offset] };
        ruleBase[i] = newRule;
        offset += 5;
    }
    return ruleBase;
}

int RulesEngine::checkRules(data *dataIn, rule* rulesBase) {
    int numMatches = 0;
    int numConditions = dataIn[0].size;

    for (int i = 0; i < NUM_RULES; i++) {
        for (int j = 0; j < numConditions; j++) {
            if (isEqual(dataIn[j].var, rulesBase[i].condition, 5)) {
                numMatches++;
                break;
            }
        }
    }

    return numMatches;
}

bool RulesEngine::isEqual(int *a, int *b, int size) {
    for( int i = 0; i < size; i++ ) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

