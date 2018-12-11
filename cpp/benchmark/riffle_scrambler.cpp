//
// Created by konrad on 10.12.18.
//

#include <riffle/riffle_scrambler.h>

#include <chrono>
#include <iostream>
#include <string>
#include <cmath>


using namespace std;


uint64_t get_depth_for_width_and_vertices(const uint64_t width, const uint64_t vertices) {
    const double width_d = static_cast<double>(width);
    const double vertices_d = static_cast<double>(vertices);

    return ceil(vertices_d / ((2 * width_d + 1) * pow(2.0, width_d)));
}


double get_time_per_node(const double execution_time, const uint64_t width, const uint64_t depth) {
    const double width_d = static_cast<double>(width);
    const double depth_d = static_cast<double>(depth);

    return execution_time / (pow(2.0, width_d) * (2.0 * width_d + 1) * depth_d);
}


double get_time_per_node_vertices(const double execution_time, const uint64_t width, const uint64_t vertices) {
    return get_time_per_node(execution_time, width, get_depth_for_width_and_vertices(width, vertices));
}


double benchmark_riffle_scrambler_call(const uint64_t width, const uint64_t depth,
                                     const string pass = "pass", const string salt = "salt",
                                     const string hash_func = "md5") {

    const auto start(chrono::high_resolution_clock::now());
    const auto result = riffle_scrambler(pass, salt, width, depth, hash_func);
    const auto end(chrono::high_resolution_clock::now());

    std::chrono::duration<double, std::milli> fp_ms = end - start;

    return fp_ms.count();
}

