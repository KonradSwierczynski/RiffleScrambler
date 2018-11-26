//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/riffle_shuffle.h>
#include <riffle/PRBG.h>
#include <riffle/HashFunctions/hashPRBG.h>

#include <string>
#include <memory>
#include <set>

class bitReader: public PRBG {
    uint64_t position;
    const std::string bits;

public:
    bitReader(const std::string bits): position{0}, bits{bits} {
    }

    bool getNextBit() override {
        return bits[position++] == '1';
    }
};

TEST_CASE("Riffle shuffle for given bits", "[riffle_shuffle]") {
    const std::string bits = "11000110111000100101100101101011010110011001000011010000101001000100000111101110001101111111000101011101111101101001100110000010010110011111010011011111001001001001000110000001100010100110000011101010100100110010001000110011100010110010100001110001111010010100110001001011011110001111000111101001010011111000101100101011100100111001101101101011111100100101100000111011101111001111001";
    auto prbg = std::make_shared<bitReader>(bits);

    SECTION("Pemrutation len = 2") {
        const auto perm = riffle_shuffle(2, prbg);
        std::vector<uint64_t> expected_perm = {1, 0};
        REQUIRE(perm == expected_perm);
    }

    SECTION("Pemrutation len = 14") {
        const auto perm = riffle_shuffle(14, prbg);
        std::vector<uint64_t> expected_perm = {10, 6, 3, 0, 11, 1, 2, 5, 8, 7, 13, 9, 4, 12};
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
        std::vector<uint64_t> expected_perm = {9, 0, 7, 10, 8, 3, 2, 5, 4, 1, 6};
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
