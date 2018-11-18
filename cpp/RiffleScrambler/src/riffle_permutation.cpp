//
// Created by konrad on 11.11.18.
//

#include <riffle/riffle_permutation.h>


uint64_t count_zeros(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    uint64_t counter = 0;
    for(uint64_t i = 0; i < length; i++) {
        counter += bm.getBit(i, row);
    }
    return counter;
}


std::vector<uint64_t> riffle_permutation(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    const uint64_t number_of_bin_zeros = count_zeros(bm, row, length);
    std::vector<uint64_t> riffle_permutation(length);
    uint64_t zeros = 0, ones = 0;
    for (uint64_t i = 0; i < length; i++) {
        if (bm.getBit(i, row)) {
            riffle_permutation[i] = number_of_bin_zeros + ones;
            ones++;
        } else {
            riffle_permutation[i] = zeros;
            zeros++;
        }
    }
    return riffle_permutation;
}


std::vector<uint64_t> complement_riffle_permutation(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    const uint64_t number_of_bin_zeros = length - count_zeros(bm, row, length);
    std::vector<uint64_t> riffle_permutation(length);
    uint64_t zeros = 0, ones = 0;
    for (uint64_t i = 0; i < length; i++) {
        if (!bm.getBit(i, row)) {
            riffle_permutation[i] = number_of_bin_zeros + ones;
            ones++;
        } else {
            riffle_permutation[i] = zeros;
            zeros++;
        }
    }
    return riffle_permutation;
}

