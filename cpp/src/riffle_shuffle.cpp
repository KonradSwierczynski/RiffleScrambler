//
// Created by konrad on 11.11.18.
//
#include "../include/riffle_shuffle.h"
#include "../include/permutation_element.h"

#include <openssl/evp.h>
#include <openssl/sha.h>

#include <iostream>

#include <string.h>

#include <iostream>


class dummyPRBG {
public:
    dummyPRBG(const char *salt) {
        srand((unsigned int)salt[0]);
    }

    bool getNextBit() {
        bool rbit = rand() % 2 == 1;
        return rbit;
    }
};


class hashPRBG {
    unsigned char *buffor;
    unsigned int bit_position, char_position, buffor_size;
public:
    void handle_error() {}

    hashPRBG(const char *salt) {
        this->buffor = new unsigned char[SHA256_DIGEST_LENGTH];
        this->calculateNextBuffor((const unsigned char *)salt, strlen(salt));
    }

    void calculateNextBuffor(const unsigned char *message, size_t m_len) {
        std::cout << "Calculate next buffor" << std::endl;
        SHA256(message, m_len, this->buffor);
        this->bit_position = 0;
        this->char_position = 0;
        this->buffor_size = SHA256_DIGEST_LENGTH;
    }

    bool getNextBit() {
        if(this->char_position > this->buffor_size) {
            this->calculateNextBuffor(this->buffor, SHA256_DIGEST_LENGTH);
        }
        const bool bit = (this->buffor[char_position] >> this->bit_position) & 1;
        if(++(this->bit_position) > 32) {
            this->bit_position = 0;
            this->char_position++;
        }
        return bit;
    }

    ~hashPRBG() {
        delete this->buffor;
    }
};


std::vector<uint64_t> riffle_shuffle(const uint64_t length, const char *salt) {
    std::vector<PermutationElement> permutation;
    std::vector<PermutationElement> swapVector;
    swapVector.reserve(length);
    permutation.reserve(length);
    for(uint64_t i = 0; i < length; i++) {
        permutation.push_back(PermutationElement(i));
    }
    hashPRBG prbg(salt);
    bool goodPermutation = false;
    uint64_t iterations = 0;

    while(!goodPermutation) {
        if (length >= (1 << 17) && iterations > 40) {
            std::cout << "Iteration: " << iterations << std::endl;
        }
        uint64_t numOfOnes = 0;
        for(uint64_t i = 0; i < length; i++) {
            bool newBit = prbg.getNextBit();
            numOfOnes += newBit;
            if(newBit) {
                permutation[i].setBit(iterations);
            }
        }
        uint64_t lastIndex = 0, lastZeroIndex = numOfOnes;

        for(uint64_t i = 0; i < length; i++) {
            if(permutation[i].getBit(iterations)) {
                swapVector[lastIndex++] = permutation[i];
            } else {
                swapVector[lastZeroIndex++] = permutation[i];
            }
        }

        std::swap(permutation, swapVector);

        goodPermutation = true;
        for(uint64_t i = 1; i < length; i++) {
            if(permutation[i].getV() == permutation[i - 1].getV()) {
                goodPermutation = false;
                break;
            }
        }

        iterations++;
    }

    std::cout << "Iterations: " << iterations << std::endl;
    std::vector<uint64_t> finishedPermutation(length);
    for(uint64_t i = 0; i < length; i++) {
        finishedPermutation[i] = permutation[i].getId();
    }

    return finishedPermutation;
}
