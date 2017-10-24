#include <fstream>
#include <iostream>
#include "Ingester.h"

data* Ingester::readFile(const char* path) {
    std::ifstream file(path);
    std::string str;
    auto dataIn = new data[32];
    unsigned j = 0;
    while (std::getline(file, str))
    {
        data dataItem = { new int[5], 5, 0 };
        int bit;
        for (unsigned long i = 0; i < 5; i++) {
            bit = (int) str.at(i) - 48;
            dataItem.var[i] = bit;
        }
        dataItem.group = (int) str.at(6) - 48;
        dataIn[j] = dataItem;
        j++;
    }
    return dataIn;
}
