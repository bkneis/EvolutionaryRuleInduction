#include <iostream>
#include "RulesEngine.h"
#include "config.h"

rule *RulesEngine::generateRuleBase(int* chromosome) {
    auto ruleBase = new rule[NUM_RULES];
    int offset = 0;
    for(int i = 0; i < NUM_RULES; i++) {
        auto condition = new int[DATA_LENGTH];
        for (int j = 0; j < DATA_LENGTH; j++) {
            condition[j] = chromosome[j + offset];
        }
        // DATA_LENGTH + 1 is needed due to whitespace
        rule newRule = { condition, DATA_LENGTH, chromosome[DATA_LENGTH + 1 + offset] };
        ruleBase[i] = newRule;
        offset += DATA_LENGTH;
    }
    return ruleBase;
}

int RulesEngine::checkRules(data *dataIn, rule* rulesBase) {
    int numMatches = 0;

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < NUM_RULES; j++) {
            if (isEqual(dataIn[i].var, rulesBase[j].condition, dataIn[0].size)) {
                if (dataIn[i].group == rulesBase[i].output) {
                    numMatches++;
                }
                break;
            }
        }
    }

    return numMatches;
}

bool RulesEngine::isEqual(int *a, int *b, int size) {
    for( int i = 0; i < size; i++ ) {
        // If a wildcard, skip the check. Check both arrays so i don't ned to bother having the first as the rules
        if (a[i] == 2 || b[i] == 2) {
            continue;
        }
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

