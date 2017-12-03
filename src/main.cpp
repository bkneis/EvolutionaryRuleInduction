#include <Environment.h>

/**
 * Main function for the application to perform the GA over configured generations
 * @return appStatusCode
 */
int main() {

    typedef unsigned long fitnessType;

    auto conf = new Config(2000, 65, 2000, 100, 20, 8, 5, 6, 1600, "../results/result_");
    auto rulesEngine = new RulesEngine(5, 6);
    auto evaluation = new FPRuleEvaluation<fitnessType>(rulesEngine);
    auto environment = new Environment<fitnessType>(conf, rulesEngine, evaluation);

    environment->run();

    return 0;
}
