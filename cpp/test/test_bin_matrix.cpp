//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/BinMatrix.h>

#include <limits>

TEST_CASE("Bin Matrix - Small vector", "[binmatrix]") {
    BinMatrix m({1, 2, 3});
    /*
    col    0-1-2
    row 1: 0 1 1
    row 0: 1 0 1
     */

    REQUIRE(m.getBit(0, 0) == 1);
    REQUIRE(m.getBit(0, 1) == 0);
    REQUIRE(m.getBit(1, 0) == 0);
    REQUIRE(m.getBit(1, 1) == 1);
    REQUIRE(m.getBit(2, 0) == 1);
    REQUIRE(m.getBit(2, 1) == 1);
}

TEST_CASE("Bin Matrix - Big vector", "[binmatrix]") {
    const uint64_t bin_len = 20;
    const std::vector<uint64_t> v(uint64_t(1) << bin_len);
    BinMatrix m(v); // Matrix 1<<bin_len x 64 with zeros

    REQUIRE(m.getBit(0, 0) == 0);
    for (uint64_t i = 0; i < bin_len; i++) {
        REQUIRE(m.getBit(uint64_t(1) << i, uint64_t(1) << i) == 0);
    }
}

TEST_CASE("Bin Matrix - Max int values", "[binmatrix") {
    const uint64_t vector_size = 10;
    std::vector<uint64_t> v;
    for (uint64_t i = 0; i < vector_size; i++) {
        v.push_back(std::numeric_limits<uint64_t>::max());
    }
    const BinMatrix m(v); // Matrix vector_size x 64 filled with ones

    for (uint64_t row = 0; row < 64; row++) {
        for (uint64_t column = 0; column < vector_size; column++) {
            REQUIRE(m.getBit(column, row) == 1);
        }
    }
}
