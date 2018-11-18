//
// Created by konrad on 11.11.18.
//

#ifndef CPP_RIFFLE_PERMUTATION_H
#define CPP_RIFFLE_PERMUTATION_H

#include <vector>
#include <cstdint>
#include <riffle/BinMatrix.h>

std::vector<uint64_t> riffle_permutation(const BinMatrix bm, const uint64_t row, const uint64_t length);


std::vector<uint64_t> complement_riffle_permutation(const BinMatrix bm, const uint64_t row, const uint64_t length);


#endif //CPP_RIFFLE_PERMUTATION_H
