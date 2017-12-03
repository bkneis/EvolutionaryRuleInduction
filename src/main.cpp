#include <GA/Environment.h>
#include <RuleMutator.h>

/**
 * Main function for the application to perform the GA over configured generations
 * @return appStatusCode
 */
int main() {

    typedef unsigned long fitnessType;

    auto conf = new GA::Config(2000, 65, 2000, 100, 20, 8, 5, 6, 1600, "../results/result_");
    auto rulesEngine = new RulesEngine(5, 6);
    auto evaluation = new FPRuleEvaluation<fitnessType>(rulesEngine);
    auto mutator = new RuleMutator<fitnessType>();
    auto environment = new GA::Environment<fitnessType>(conf, rulesEngine, evaluation, mutator);

    environment->run();

    return 0;
}
