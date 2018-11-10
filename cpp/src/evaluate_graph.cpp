//
// Created by konrad on 11.11.18.
//

#include "../include/evaluate_graph.h"

#include <iostream>

std::string foo(const std::string a) {
    return a;
}

std::string foo(const std::string a, const std::string b) {
    return a;
}

std::string eval_graph(const std::vector<std::vector<std::vector<uint64_t>>> edges, const uint64_t depth, const uint64_t g, const std::string value) {
    const uint64_t length = 1 << g;
    std::vector<std::string> first_row(length), second_row(length);
    first_row[0] = foo(value);
    for(uint64_t i = 1; i < length; i++) {
        first_row[i] = foo(first_row[i - 1]);
    }

    for(uint64_t d = 0; d < depth; d++) {
        std::cout << "Depth: " << d << std::endl;
        for(uint64_t row = 0; row < 2 * g; row++) {

            second_row[0] = foo(first_row[length - 1]);
            for(uint64_t parent: edges[row][0]) {
                second_row[0] = foo(second_row[0], first_row[parent]);
            }

            for(uint64_t i = 1; i < length; i++) {
                second_row[i] = foo(second_row[i - 1]);
                for(uint64_t parent: edges[row][i]) {
                    second_row[i] = foo(second_row[i], first_row[parent]);
                }
            }

            std::swap(first_row, second_row);
        }
    }

   return second_row[length - 1];
}
