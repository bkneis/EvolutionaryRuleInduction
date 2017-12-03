#include <fstream>
#include <iostream>
#include <Ingester.h>
#include <vector>
#include <sstream>

data* Ingester::readFile(const char* path) {
    std::ifstream file(path);
    std::string str;
    auto dataIn = new data[NUMBER_OF_DATA];
    unsigned j = 0;
    while (std::getline(file, str))
    {
        std::string buf; // Have a buffer string
        std::stringstream ss(str); // Insert the string into a stream

        std::vector<std::string> tokens; // Create vector to hold our words

        while (ss >> buf) tokens.push_back(buf);

        data dataItem = { new float[DATA_LENGTH], DATA_LENGTH, 0 };

        for (int i = 0; i < DATA_LENGTH; i++) {
            dataItem.var[i] = std::stof(tokens.at(i));
        }

        dataItem.group = stoi(tokens.at(DATA_LENGTH)); // Get the class value
        dataIn[j] = dataItem;
        j++;
    }
    return dataIn;
}
