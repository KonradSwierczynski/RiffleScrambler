#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <string>
#include <stdlib.h>


std::vector<long> riffle_shuffle(const long length, const char *salt);


int main() {
    auto perm = riffle_shuffle(100000, "test");
    std::cout << "Done!" << std::endl;
    return 0;
}




class PermutationElement {
    std::string value;
    long id;
    long v;

public:
    PermutationElement(const long id) {
        this->id = id;
        this->v = 0;
        this->value = "";
    }

    bool getBit(long index) {
        return (this->v >> index) & 1;
    }

    char getFirstBit() {
        char firstBit = this->value.at(0);
        return firstBit == '1';
    }

    void setBit(long index) {
        this->v |= 1<<index;
    }

    void addBit(bool bit) {
        this->value.insert(0, 1, bit ? '1' : '0');
    }

    long getId() {
        return this->id;
    }

    long getV() {
        return this->v;
    }

    std::string getValue() {
        return this->value;
    }
};

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

std::vector<long> riffle_shuffle(const long length, const char *salt) {
    std::vector<PermutationElement> permutation;
    std::vector<PermutationElement> swapVector;
    swapVector.reserve(length);
    for(long i = 0; i < length; i++) {
        permutation.push_back(PermutationElement(i));
    }
    dummyPRBG prbg(salt);
    bool goodPermutation = false;
    long iterations = 0;

    while(!goodPermutation) {
        iterations++;
        long numOfOnes = 0;
        for(long i = 0; i < length; i++) {
            bool newBit = prbg.getNextBit();
            numOfOnes += newBit;
            permutation[i].addBit(newBit);
        }
        long lastIndex = 0, lastZeroIndex = numOfOnes;

        for(long i = 0; i < length; i++) {
            if(permutation[i].getFirstBit()) {
                swapVector[lastIndex++] = permutation[i];
            } else {
                swapVector[lastZeroIndex++] = permutation[i];
            }
        }

        std::swap(permutation, swapVector);

        goodPermutation = true;
        for(long i = 1; i < length; i++) {
            if(permutation[i].getValue() == permutation[i - 1].getValue()) {
                goodPermutation = false;
                break;
            }
        }
    }

    std::vector<long> finishedPermutation(length);
    for(long i = 0; i < length; i++) {
        finishedPermutation[i] = permutation[i].getId();
    }

    return finishedPermutation;
}
