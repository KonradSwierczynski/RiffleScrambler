//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/hash_functions/md_utils.h>
#include <riffle/hash_functions/HashResult.h>
#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>

#include <string>
#include <vector>

using namespace std;

TEST_CASE("Evalueate graph - g = 1", "[eval]") {
    const uint64_t g = 1;
    const vector<vector<uint64_t>> row = {{0, 1}, {0, 1}};
    const riffle_graph graph = {row, row};
    const string value = "test";
    const auto wrapper = get_md_by_name("sha256");

    SECTION("Depth: 1") {
        const uint64_t depth = 1;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.length(), wrapper);
        REQUIRE(
            result.toString() ==
            "bfcfc35ea293f8692a133cf751a48571f5f0d124ff249f020daf62dc02be630d");
    }

    SECTION("Depth: 2") {
        const uint64_t depth = 2;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.size(), wrapper);
        REQUIRE(
            result.toString() ==
            "7df2eaa633c7e55101a97f25c26af17e7bd44ff1c1795bd65a933551abc331d6");
    }

    SECTION("Depth: 10") {
        const uint64_t depth = 10;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.size(), wrapper);
        REQUIRE(
            result.toString() ==
            "91f35ab87d664d3e1d6d07251a8068969e620912df6eced620b3d622f651baf5");
    }
}

TEST_CASE("Evalueate graph - g = 2", "[eval]") {
    const uint64_t g = 2;
    const vector<vector<uint64_t>> row = {{0, 2}, {1, 2}, {0, 3}, {1, 3}};
    const riffle_graph graph = {row, row, row, row};
    const string value = "Some value, it can be anything, any length..... 0987654321?>~@\n~ąć?";
    const auto wrapper = get_md_by_name("sha256");

    SECTION("Depth: 1") {
        const uint64_t depth = 1;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.size(), wrapper);
        REQUIRE(
            result.toString() ==
            "2ef148438b75dc49cfda15f415dd5b7b2d9029fa1d8305d2973b82b1fb15b58b");
    }

    SECTION("Depth: 2") {
        const uint64_t depth = 2;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.size(), wrapper);
        REQUIRE(
            result.toString() ==
            "df6ab55d845d3609010cd4bd60f5f10b5ba2ebec6ddd7dfa8847ba3403d98923");
    }

    SECTION("Depth: 10") {
        const uint64_t depth = 10;
        auto result = eval_graph(graph, depth, g, value.c_str(), value.size(), wrapper);
        REQUIRE(
            result.toString() ==
            "114177c03517ff6f9c63b60a56cff9707b2a5b6bc4f151df497bd01b3a3fae3f");
    }
}
