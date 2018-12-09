//
// Created by konrad on 11.11.18.
//
#include <riffle/PRBG.h>
#include <riffle/permutation_element.h>
#include <riffle/riffle_shuffle.h>

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <string.h>


std::vector<uint64_t> riffle_shuffle(const uint64_t length,
                                     std::shared_ptr<PRBG> prbg) {
    std::vector<PermutationElement> permutation;
    std::vector<PermutationElement> swapVector;
    swapVector.reserve(length);
    permutation.reserve(length);
    for (uint64_t i = 0; i < length; i++) {
        permutation.emplace_back(i);
        swapVector.emplace_back(i);
    }

    bool goodPermutation = false;
    uint64_t iterations = 0;

    while (!goodPermutation) {
        uint64_t numOfOnes = 0;
        for (uint64_t i = 0; i < length; i++) {
            const bool newBit = prbg->getNextBit();
            numOfOnes += (uint64_t)newBit;
            if (newBit) {
                permutation[i].setBit(iterations);
            }
        }
        uint64_t lastIndex = 0, lastZeroIndex = numOfOnes;

        for (uint64_t i = 0; i < length; i++) {
            if (permutation[i].getBit(iterations)) {
                swapVector[lastIndex++] = permutation[i];
            } else {
                swapVector[lastZeroIndex++] = permutation[i];
            }
        }

        std::swap(permutation, swapVector);

        goodPermutation = true;
        for (uint64_t i = 1; i < length; i++) {
            if (permutation[i].getV() == permutation[i - 1].getV()) {
                goodPermutation = false;
                break;
            }
        }

        iterations++;
    }

    std::vector<uint64_t> finishedPermutation(length);
    for (uint64_t i = 0; i < length; i++) {
        finishedPermutation[i] = permutation[i].getId();
    }

    return finishedPermutation;
}
