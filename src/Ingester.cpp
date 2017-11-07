#include <fstream>
#include <iostream>
#include <Ingester.h>
#include "Ingester.h"
#include "config.h"

data* Ingester::readFile(const char* path) {
    std::ifstream file(path);
    std::string str;
    auto dataIn = new data[NUMBER_OF_DATA];
    unsigned j = 0;
    while (std::getline(file, str))
    {
        data dataItem = { new int[DATA_LENGTH], DATA_LENGTH, 0 };
        int bit;
        for (unsigned long i = 0; i < DATA_LENGTH; i++) {
            bit = (int) str.at(i) - 48; // Convert ascii string to int
            dataItem.var[i] = bit;
        }
        dataItem.group = (int) str.at(DATA_LENGTH + 1) - 48; // Get the class value
        dataIn[j] = dataItem;
        j++;
    }
    return dataIn;
}
