//
// Created by konrad on 11.11.18.
//

#include <riffle/HashFunctions/HashElement.h>
#include <riffle/HashFunctions/md_types.h>
#include <riffle/evaluate_graph.h>

#include <iostream>
#include <string>

std::string eval_graph(const riffle_graph edges, const uint64_t depth,
                       const uint64_t g, const std::string value,
                       const MD_Wrapper wrapper) {
    std::cout << "\tDepth: ";
    const uint64_t length = uint64_t(1) << g;
    std::vector<HashElement> first_row, second_row;
    first_row.reserve(length);
    second_row.reserve(length);
    for (uint64_t i = 0; i < length; i++) {
        first_row.emplace_back(wrapper);
        second_row.emplace_back(wrapper);
    }
    first_row[0].update(value.c_str(), value.length());
    for (uint64_t i = 1; i < length; i++) {
        first_row[i].update(first_row[i - 1]);
    }
    for (uint64_t d = 0; d < depth; d++) {
        std::cout << d << ".. ";
        for (uint64_t row = 0; row < 2 * g; row++) {

            second_row[0].update(first_row[length - 1]);
            for (uint64_t parent : edges[row][0]) {
                second_row[0].update(first_row[parent]);
            }

            for (uint64_t i = 1; i < length; i++) {
                second_row[i].update(second_row[i - 1]);
                for (uint64_t parent : edges[row][i]) {
                    second_row[i].update(first_row[parent]);
                }
            }

            std::swap(first_row, second_row);
        }
    }
    std::cout << " done!" << std::endl;

    return second_row[length - 1].toString();
}
