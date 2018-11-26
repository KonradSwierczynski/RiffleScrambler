//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/permutation_element.h>


TEST_CASE("Test permutation element", "[permutation]") {
    PermutationElement p {1};

    REQUIRE(p.getId() == uint64_t(1));
    REQUIRE(p.getV() == uint64_t(0));
    REQUIRE(p.getBit(1) == 0);

    p.setBit(1);

    REQUIRE(p.getId() == uint64_t(1));
    REQUIRE(p.getV() == uint64_t(2));
    REQUIRE(p.getBit(1) == 1);

    p.setBit(63);

    REQUIRE(p.getV() == (uint64_t(1) << 63) + uint64_t(2));
    REQUIRE(p.getBit(1) == 1);
    REQUIRE(p.getBit(63) == 1);
}

TEST_CASE("Test const permutation element", "[permutation]") {
    const PermutationElement p {1};

    REQUIRE(p.getBit(1) == 0);
    REQUIRE(p.getId() == 1);
    REQUIRE(p.getV() == 0);
}
