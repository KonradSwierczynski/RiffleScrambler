//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/riffle_permutation.h>

TEST_CASE("Riffle permutation", "[rifflepermutation]") {
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
