//
// Created by konrad on 11.11.18.
//

#include <riffle/generate_graph.h>
#include <riffle/riffle_permutation.h>

#include <iostream>


riffle_graph gen_graph(const std::vector<uint64_t> seeds, const uint64_t g) {
    std::cout << "\tGenerating graph...";
    BinMatrix bin_matrix(seeds);
    const uint64_t length = 1 << g;
    riffle_graph edges (2 * g, std::vector<std::vector<uint64_t>>(length, std::vector<uint64_t>(2)));
    for(uint64_t row = 0; row < g; row++) {
        auto rp = riffle_permutation(bin_matrix, row, length);
        for(uint64_t i = 0; i < length; i++) {
            edges[row][rp[i]][0] = i;
            edges[2 * g - row - 1][i][0] = rp[i];
        }
        auto crp = complement_riffle_permutation(bin_matrix, row, length);
        for(uint64_t i = 0; i < length; i++) {
            edges[row][crp[i]][1] = i;
            edges[2 * g - row - 1][i][1] = crp[i];
        }
    }
    std::cout << " done!" << std::endl;
    return edges;
}
