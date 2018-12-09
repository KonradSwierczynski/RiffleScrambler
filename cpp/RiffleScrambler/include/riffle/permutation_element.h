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
    PermutationElement(const uint64_t id) : id{id}, v{0} {}

    bool getBit(const uint64_t index) const {
        return ((this->v >> index) & 1) == 1;
    }

    void setBit(const uint64_t index) { this->v |= uint64_t(1) << index; }

    uint64_t getId() const { return this->id; }

    uint64_t getV() const { return this->v; }
};

#endif // CPP_PERMUTATION_ELEMENT_H
