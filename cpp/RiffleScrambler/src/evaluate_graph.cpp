//
// Created by konrad on 11.11.18.
//

#include <riffle/hash_functions/HashElement.h>
#include <riffle/hash_functions/cleanup.h>
#include <riffle/hash_functions/md_types.h>
#include <riffle/evaluate_graph.h>

#include <string>

const HashResult eval_graph(const riffle_graph &edges, const uint64_t depth,
                       const uint64_t g, const void *const password, const size_t pwdlen_bytes,
                       const MD_Wrapper wrapper) {
    const uint64_t length = uint64_t(1) << g;
    std::vector<HashElement> first_row, second_row;
    first_row.reserve(length);
    second_row.reserve(length);
    for (uint64_t i = 0; i < length; i++) {
        first_row.emplace_back(wrapper);
        second_row.emplace_back(wrapper);
    }
    first_row[0].update(password, pwdlen_bytes);
    for (uint64_t i = 1; i < length; i++) {
        first_row[i].update(first_row[i - 1]);
    }
    for (uint64_t d = 0; d < depth; d++) {
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
    const auto hash_result = second_row[length - 1].finalize();

    cleanup();

    return hash_result;
}
