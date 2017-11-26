#ifndef GENETICALGORITHM_UTIL_H
#define GENETICALGORITHM_UTIL_H

#include <cstdlib>

/**
 * Generate a random number of a given type between min and max
 * @tparam T
 * @param min
 * @param max
 * @return
 */
template <typename T = int>
inline T getRandomNumber(int min, int max) {
    return static_cast<T>(rand() % (max + 1) + min);
}

/**
 * Create a results file to save the fitness values to per generation. Then return the file path.
 * @return path
 */
inline std::string createResultsFile() {
    // Create the results file and enter the configuration values
    std::ofstream resultsFile;
    time_t now = time(0);
    char* dt = ctime(&now);
    std::ostringstream path;
    path << "../results/results_" << dt << ".csv";
    resultsFile.open(path.str(), std::ios_base::app);

    if (resultsFile.is_open()) {
        resultsFile << NUMBER_OF_GENERATIONS << ","
                    << NUMBER_OF_CHROMOSOMES << ","
                    << SIZE_OF_POPULATION << ","
                    << PROBABILITY_OF_CROSSOVER << ","
                    << PROBABILITY_OF_MUTATION;

        resultsFile.close();
        return path.str();
    }

    throw "Could not write to the results file";
}

#endif //GENETICALGORITHM_UTIL_H
