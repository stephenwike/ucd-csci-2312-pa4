//
// Created by Stephen on 11/10/2015.
//

#include "IdGen.h"

namespace Clustering {

    template<typename T>
    unsigned int IdGen<T>::id_curr = 1;

    template<typename T>
    IdGen<T>::IdGen() {
        id_id = id_curr++;
    }

    template<typename T>
    void IdGen<T>::rewindIdGen(T) {
        id_id = id_curr--;
    }
};