//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/generate_graph.h>

#include <string>
#include <vector>

using namespace std;

TEST_CASE("Generate graph for given permutation - g = 1", "[generate]") {
    const uint64_t g = 1;

    SECTION("Permutation {0, 1}") {
        const vector<uint64_t> seed = {0, 1};
        auto graph = gen_graph(seed, g);
        riffle_graph expected_graph = {{{0, 1}, {1, 0}}, {{0, 1}, {1, 0}}};
        REQUIRE(graph == expected_graph);
    }

    SECTION("Permutation {1, 0}") {
        const vector<uint64_t> seed = {1, 0};
        auto graph = gen_graph(seed, g);
        riffle_graph expected_graph = {{{1, 0}, {0, 1}}, {{1, 0}, {0, 1}}};
        REQUIRE(graph == expected_graph);
    }
}

TEST_CASE("Generate graph for given permutation - g = 2", "[generate]") {
    const vector<uint64_t> seed = {3, 1, 2, 0};
    const uint64_t g = 2;
    auto graph = gen_graph(seed, g);
    riffle_graph expected_graph = {{{2, 0}, {3, 1}, {0, 2}, {1, 3}},
                                   {{1, 0}, {3, 2}, {0, 1}, {2, 3}},
                                   {{2, 0}, {0, 2}, {3, 1}, {1, 3}},
                                   {{2, 0}, {3, 1}, {0, 2}, {1, 3}}};

    REQUIRE(graph == expected_graph);
}
