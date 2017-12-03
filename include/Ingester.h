#ifndef GENETICALGORITHM_INGESTER_H
#define GENETICALGORITHM_INGESTER_H

typedef struct {
    float* var;
    int size;
    int group;
} data;

class Ingester {

public:
    Ingester(int numData, int dataLength) {
        this->NUMBER_OF_DATA = numData;
        this->DATA_LENGTH = dataLength;
    }
    data* readFile(const char* path);

private:
    int NUMBER_OF_DATA;
    int DATA_LENGTH;

};


#endif //GENETICALGORITHM_INGESTER_H
