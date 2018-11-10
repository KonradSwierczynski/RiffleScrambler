//
// Created by konrad on 14.11.18.
//

#ifndef CPP_PERMUTATION_ELEMENT_H
#define CPP_PERMUTATION_ELEMENT_H

#include <cstdint>

class PermutationElement {
    uint64_t id;
    uint64_t v;

public:
    PermutationElement(const uint64_t id) {
        this->id = id;
        this->v = 0;
    }

    bool getBit(uint64_t index) {
        return (this->v >> index) & 1;
    }

    void setBit(uint64_t index) {
        this->v |= 1<<index;
    }

    uint64_t getId() {
        return this->id;
    }

    uint64_t getV() {
        return this->v;
    }
};

#endif //CPP_PERMUTATION_ELEMENT_H
