//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/PRBG.h>
#include <riffle/riffle_shuffle.h>

#include <memory>
#include <set>
#include <string>

class bitReader : public PRBG {
    uint64_t position;
    const std::string bits;

  public:
    bitReader(const std::string bits) : position{0}, bits{bits} {}

    bool getNextBit() override { return bits[position++] == '1'; }
};

TEST_CASE("Riffle shuffle for given bits", "[riffle_shuffle]") {
    const std::string bits =
        "1100011011100010010110010110101101011001100100001101000010100100010000"
        "0111101110001101111111000101011101111101101001100110000010010110011111"
        "0100110111110010010010010001100000011000101001100000111010101001001100"
        "1000100011001110001011001010000111000111101001010011000100101101111000"
        "1111000111101001010011111000101100101011100100111001101101101011111100"
        "100101100000111011101111001111001";
    auto prbg = std::make_shared<bitReader>(bits);

    SECTION("Pemrutation len = 2") {
        const auto perm = riffle_shuffle(2, prbg);
        std::vector<uint64_t> expected_perm = {1, 0};
        REQUIRE(perm == expected_perm);
    }

    SECTION("Pemrutation len = 14") {
        const auto perm = riffle_shuffle(14, prbg);
        std::vector<uint64_t> expected_perm = {10, 6, 3, 0,  11, 1, 2,
                                               5,  8, 7, 13, 9,  4, 12};
        REQUIRE(perm == expected_perm);
    }
}

TEST_CASE("Riffle shuffle for hash PRBG", "[riffle_shuffle]") {
    const std::string salt = "salt";
    auto prbg = std::make_shared<hashPRBG>(salt.c_str(), salt.size());

    SECTION("Permutaion len = 4") {
        const auto perm = riffle_shuffle(4, prbg);
        std::vector<uint64_t> expected_perm = {1, 2, 0, 3};
        REQUIRE(perm == expected_perm);
    }

    SECTION("Permutation len = 11") {
        const auto perm = riffle_shuffle(11, prbg);
        std::vector<uint64_t> expected_perm = {9, 0, 7, 10, 8, 3,
                                               2, 5, 4, 1,  6};
        REQUIRE(perm == expected_perm);
    }

    SECTION("Permutation len = 1 << 20") {
        const uint64_t size = uint64_t(1) << 20;
        const auto perm = riffle_shuffle(size, prbg);
        REQUIRE(perm.size() == size);
        REQUIRE(std::set<uint64_t>(perm.begin(), perm.end()).size() == size);
    }
}

/*
TEST_CASE("Riffle shuffle for given bits", "[riffleshuffle]") {
    const uint64_t bit_len = 20;

    SECTION("Bits for salt: 'salt'") {
        auto prbg = std::make_shared<readerPRBG>("bit_salt.txt");
        auto res = riffle_shuffle(uint64_t(1) << bit_len, prbg);
        std::cout << "Bits: " << prbg->getReadBits() << std::endl;
    }
    SECTION("Broken bits") {
        auto prbg = std::make_shared<readerPRBG>("bit_salt_noOpt.txt");
        auto res = riffle_shuffle(uint64_t(1) << bit_len, prbg);
        std::cout << "Broken bits: " << prbg->getReadBits() << std::endl;
    }
}
*/
