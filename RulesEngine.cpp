//
// Created by arthur on 17/10/17.
//

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

int RulesEngine::checkRules(data* dataIn, int* chromosome) {
    int numMatches = 0;
    int numConditions = dataIn[0].size;
    int offset = 0;
    bool breaking = false;
    // For each data item
    for (int i = 0; i < 32; i++) {
        // For each rule
        for (int j = 0; j < NUM_RULES; j++) {
            // If the data item is the same structure as the rule
            if (breaking) {
                breaking = false;
                break;
            }
            for (int k = 0; k < numConditions; k++) {
                // If the current index of the chromosome gene is not the same, skip that chromosome
                if(chromosome[k + offset] != dataIn[i].var[k]) {
                    offset += 5;
                    break;
                }
                // If the loop has gotten to the end
                if (k == (numConditions - 1)) {
                    // Check that the class and output is the same
                    if (chromosome[5 + offset] == dataIn[i].group) {
                        numMatches++;
                        breaking = true;
                    }
                }
            }
            // Move the window
            offset += 5;
        }
    }
    return numMatches;
}
