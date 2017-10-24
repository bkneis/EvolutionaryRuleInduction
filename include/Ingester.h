//
// Created by arthur on 17/10/17.
//

#ifndef GENETICALGORITHM_INGESTER_H
#define GENETICALGORITHM_INGESTER_H

typedef struct {
    int* var;
    int size;
    int group;
} data;

class Ingester {

public:

    data* readFile(const char* path);

};


#endif //GENETICALGORITHM_INGESTER_H
