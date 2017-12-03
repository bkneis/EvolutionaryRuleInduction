#ifndef EVOLVINGRULEINDUCTIONSYSTEM_IMUTATE_H
#define EVOLVINGRULEINDUCTIONSYSTEM_IMUTATE_H

#include "Individual.h"

namespace GA {

    template <typename fitnessType>
    class IMutatable {

    public:
        virtual void mutate(Individual<fitnessType>* individual, GA::Config* conf) = 0;

    };

}

#endif //EVOLVINGRULEINDUCTIONSYSTEM_IMUTATE_H
