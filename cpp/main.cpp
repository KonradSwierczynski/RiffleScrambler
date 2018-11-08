#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <string>
#include <stdlib.h>


std::vector<uint64_t> riffle_shuffle(const uint64_t length, const char *salt);
std::vector<uint64_t> riffle_permutation(const uint64_t value, const uint64_t length);
std::vector<uint64_t> complement_riffle_permutation(uint64_t value, const uint64_t length);
std::vector<std::vector<std::vector<uint64_t> > > gen_graph(const std::vector<uint64_t> seeds, const uint64_t g);
bool get_bit(uint64_t value, uint64_t index);

void riffle_shuffle_t(const uint64_t len) {
    auto perm = riffle_shuffle(len, "test");
    std::cout << "Done!" << std::endl;
}

void riffle_perm_t(const uint64_t val, const uint64_t len) {
    auto perm = riffle_permutation(val, len);
    for(uint64_t i = 0; i < len; i++) {
        std::cout << perm[i] << " ";
    }
    std::cout << std::endl << "RPerm done!" << std::endl;
}

void c_riffle_perm_t(const uint64_t val, const uint64_t len) {
    auto perm = complement_riffle_permutation(val, len);
    for(uint64_t i = 0; i < len; i++) {
        std::cout << perm[i] << " ";
    }
    std::cout << std::endl << "C RPerm done!" << std::endl;
}


void get_bit_t() {
    uint64_t num = 228;
    for(uint64_t i = 0; i < 8; i++) {
        std::cout << get_bit(num, 8 - i - 1) << " ";
    }
    std::cout << std::endl;
}

void gen_g_t() {
    uint64_t num = 5, g = 15;
    auto perm = riffle_shuffle(1 << g, "test");
    std::cout << "RF finished" << std::endl;
    auto grap = gen_graph(perm, g);
}

int main() {
//    riffle_perm_t(228, 8);
//    riffle_perm_t(27, 8);
//    c_riffle_perm_t(228, 8);
//    c_riffle_perm_t(27, 8);
//    riffle_shuffle_t(100000);
    gen_g_t();
    return 0;
}


uint64_t count_zeros(uint64_t value, uint64_t length) {
    uint64_t counter = 0;
    for(uint64_t i = 0; i < length; i++) {
        counter += ((value >> i) & 1) == 0;
    }
    return counter;
}

bool get_bit(uint64_t value, uint64_t index) {
    return (value >> index) & 1;
}



class BinMatrix {
    std::vector<uint64_t> values;
public:
    BinMatrix(const std::vector<uint64_t> values) {
        this->values = values;
    }

    bool getBit(const uint64_t column, const uint64_t row) const {
        return (this->values[column] >> row) & 1;
    }
};


uint64_t count_zeros_bm(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    uint64_t counter = 0;
    for(uint64_t i = 0; i < length; i++) {
        counter += bm.getBit(i, row);
    }
    return counter;
}

std::vector<uint64_t> c_riffle_permutation_bm(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    const uint64_t number_of_bin_zeros = length - count_zeros_bm(bm, row, length);
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

std::vector<uint64_t> riffle_permutation_bm(const BinMatrix bm, const uint64_t row, const uint64_t length) {
    const uint64_t number_of_bin_zeros = count_zeros_bm(bm, row, length);
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

std::vector<std::vector<std::vector<uint64_t> > > gen_graph(const std::vector<uint64_t> seeds, const uint64_t g) {
    BinMatrix bin_matrix(seeds);
    const uint64_t length = 1 << g;
    std::vector<std::vector<std::vector<uint64_t> > > edges (2 * g, std::vector<std::vector<uint64_t> >(length, std::vector<uint64_t>()));
    for(uint64_t row = 0; row < g; row++) {
        auto rp = riffle_permutation_bm(bin_matrix, row, length);
        for(uint64_t i = 0; i < length; i++) {
            edges[row][rp[i]].push_back(i);
            edges[2 * g - row - 1][i].push_back(rp[i]);
        }
        auto crp = c_riffle_permutation_bm(bin_matrix, row, length);
        for(uint64_t i = 0; i < length; i++) {
            edges[row][crp[i]].push_back(i);
            edges[2 * g - row - 1][i].push_back(crp[i]);
        }
    }
    return edges;
}


std::vector<uint64_t> riffle_permutation(const uint64_t value, const uint64_t length) {
     const uint64_t number_of_bin_zeros = count_zeros(value, length);
    std::vector<uint64_t> riffle_permutation(length);
    uint64_t zeros = 0, ones = 0;
    for (uint64_t i = 0; i < length; i++) {
        if (get_bit(value, length - i - 1)) {
            riffle_permutation[i] = number_of_bin_zeros + ones;
            ones++;
        } else {
            riffle_permutation[i] = zeros;
            zeros++;
        }
    }
    return riffle_permutation;
}


std::vector<uint64_t> complement_riffle_permutation(uint64_t value, const uint64_t length) {
    return riffle_permutation(~value, length);
}


class PermutationElement {
    std::string value;
    uint64_t id;
    uint64_t v;

public:
    PermutationElement(const uint64_t id) {
        this->id = id;
        this->v = 0;
        this->value = "";
    }

    bool getBit(uint64_t index) {
        return (this->v >> index) & 1;
    }

    char getFirstBit() {
        char firstBit = this->value.at(0);
        return firstBit == '1';
    }

    void setBit(uint64_t index) {
        this->v |= 1<<index;
    }

    void addBit(bool bit) {
        this->value.insert(0, 1, bit ? '1' : '0');
    }

    uint64_t getId() {
        return this->id;
    }

    uint64_t getV() {
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

std::vector<uint64_t> riffle_shuffle(const uint64_t length, const char *salt) {
    std::vector<PermutationElement> permutation;
    std::vector<PermutationElement> swapVector;
    swapVector.reserve(length);
    for(uint64_t i = 0; i < length; i++) {
        permutation.push_back(PermutationElement(i));
    }
    dummyPRBG prbg(salt);
    bool goodPermutation = false;
    uint64_t iterations = 0;

    while(!goodPermutation) {
        iterations++;
        uint64_t numOfOnes = 0;
        for(uint64_t i = 0; i < length; i++) {
            bool newBit = prbg.getNextBit();
            numOfOnes += newBit;
            permutation[i].addBit(newBit);
        }
        uint64_t lastIndex = 0, lastZeroIndex = numOfOnes;

        for(uint64_t i = 0; i < length; i++) {
            if(permutation[i].getFirstBit()) {
                swapVector[lastIndex++] = permutation[i];
            } else {
                swapVector[lastZeroIndex++] = permutation[i];
            }
        }

        std::swap(permutation, swapVector);

        goodPermutation = true;
        for(uint64_t i = 1; i < length; i++) {
            if(permutation[i].getValue() == permutation[i - 1].getValue()) {
                goodPermutation = false;
                break;
            }
        }
    }

    std::vector<uint64_t> finishedPermutation(length);
    for(uint64_t i = 0; i < length; i++) {
        finishedPermutation[i] = permutation[i].getId();
    }

    return finishedPermutation;
}



