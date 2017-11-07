#include <iostream>
#include <RulesEngine.h>
#include "config.h"

rule *RulesEngine::generateRuleBase(float* chromosome) {
    auto ruleBase = new rule[NUM_RULES];
    int offset = 0;
    for(int i = 0; i < NUM_RULES; i++) {
        auto condition = new float[DATA_LENGTH * 2];
        for (int j = 0; j < DATA_LENGTH * 2; j++) {
            condition[j] = chromosome[j + offset];
        }
        rule newRule = { condition, DATA_LENGTH * 2, chromosome[DATA_LENGTH * 2 + offset] };
        ruleBase[i] = newRule;
        offset += DATA_LENGTH * 2 + 1;
    }
    return ruleBase;
}

int RulesEngine::checkRules(data *dataIn, rule* rulesBase) {
    int numMatches = 0;

    for (int i = 0; i < NUMBER_OF_DATA; i++) {
        for (int j = 0; j < NUM_RULES; j++) {
            if (isEqual(dataIn[i].var, rulesBase[j].condition, dataIn[0].size)) {
                if (dataIn[i].group == rulesBase[j].output) {
                    numMatches++;
                }
                break;
            }
        }
    }

    return numMatches;
}

bool RulesEngine::isEqual(float* data, float* rule, int size) {
    int j = 0;
    for( int i = 0; i < size / 2; i++) {
        float top = rule[j] > rule[j + 1] ? rule[j] : rule[j + 1];
        float bottom = rule[j] < rule[j + 1] ? rule[j] : rule[j + 1];
        if (data[i] < top && data[i] > bottom) {
            j += 2;
            continue;
        }
        return false;
    }
    return true;
}

