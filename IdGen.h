//
// Created by Stephen on 11/10/2015.
//

#ifndef PA4_IDGEN_H
#define PA4_IDGEN_H

namespace Clustering {

    template<typename T>
    class IdGen {
    protected:
        static unsigned int id_curr;
    public:
        unsigned int id_id;
        IdGen();
        void rewindIdGen(T);
    };

};

#include "IdGen.cpp"
#endif //PA4_IDGEN_H