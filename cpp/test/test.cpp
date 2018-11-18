//
// Created by konrad on 12.11.18.
//

#include "catch.hpp"

#include <vector>

#include "riffle/BinMatrix.h"
#include "riffle/riffle_permutation.h"

TEST_CASE( "Bin Matrix - Small vector", "[binmatrix]" ) {
    BinMatrix m({1, 2, 3});
    /*
    col    0 1 2
    row 1: 0 1 1
    row 0: 1 0 1
     */

    REQUIRE(m.getBit(0, 0) == true);
    REQUIRE(m.getBit(0, 1) == false);
    REQUIRE(m.getBit(1, 0) == false);
    REQUIRE(m.getBit(1, 1) == true);
    REQUIRE(m.getBit(2, 0) == true);
    REQUIRE(m.getBit(2, 1) == true);
}

TEST_CASE( "Bin Matrix - Big vector", "[binmatrix]" ) {
    const std::vector<uint64_t> v(uint64_t(1) << 14);
    BinMatrix m(v);

    REQUIRE(m.getBit(0, 0) == false);
    REQUIRE(m.getBit(uint64_t(1) << 13, uint64_t(1) << 13) == false);
}

TEST_CASE( "Riffle permutation", "[rifflepermutation]" ) {
    const std::vector<uint64_t> v{1, 1, 1, 0, 0, 1, 0, 0};
    BinMatrix m(v);

    SECTION("Normal riffle permutation") {
        auto permutation = riffle_permutation(m, 0, v.size());
        std::vector<uint64_t> expected{4, 5, 6, 0, 1, 7, 2, 3};
        REQUIRE(permutation == expected);
    }
    SECTION("Complement riffle permutation") {
        auto permutation = complement_riffle_permutation(m, 0, v.size());
        std::vector<uint64_t> expected{0, 1, 2, 4, 5, 3, 6, 7};
        REQUIRE(permutation == expected);
    }
}