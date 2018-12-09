//
// Created by konrad on 24.11.18.
//

#include "catch.hpp"

#include <riffle/hash_functions/md__utils.h>
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
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "bfcfc35ea293f8692a133cf751a48571f5f0d124ff249f020daf62dc02be630d");
    }

    SECTION("Depth: 2") {
        const uint64_t depth = 2;
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "7df2eaa633c7e55101a97f25c26af17e7bd44ff1c1795bd65a933551abc331d6");
    }

    SECTION("Depth: 10") {
        const uint64_t depth = 10;
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "91f35ab87d664d3e1d6d07251a8068969e620912df6eced620b3d622f651baf5");
    }
}

TEST_CASE("Evalueate graph - g = 2", "[eval]") {
    const uint64_t g = 2;
    const vector<vector<uint64_t>> row = {{0, 2}, {1, 2}, {0, 3}, {1, 3}};
    const riffle_graph graph = {row, row, row, row};
    const string value =
        "Some initial value, it can be anything, any length..... 0987654321?>~";
    const auto wrapper = get_md_by_name("sha256");

    SECTION("Depth: 1") {
        const uint64_t depth = 1;
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "fcdaa0841b33f01567fbe72440c29b0eb22c4ec5e901ec9742fe71353f788ece");
    }

    SECTION("Depth: 2") {
        const uint64_t depth = 2;
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "04054a9170290cb72f984f8c85af72ae09b68fe20dc42cab17a36e7fa9242ccd");
    }

    SECTION("Depth: 10") {
        const uint64_t depth = 10;
        auto result = eval_graph(graph, depth, g, value, wrapper);
        REQUIRE(
            result ==
            "936c6a84d2695f29ac054b077d0c50f770b8afc20fd3dbe9a933641f96c9bd23");
    }
}
