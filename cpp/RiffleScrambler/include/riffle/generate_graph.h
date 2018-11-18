//
// Created by konrad on 11.11.18.
//

#ifndef CPP_GENERATE_GRAPH_H
#define CPP_GENERATE_GRAPH_H

#include <cstdint>
#include <vector>
#include <riffle/BinMatrix.h>

std::vector<std::vector<std::vector<uint64_t> > > gen_graph(const std::vector<uint64_t> seeds, const uint64_t g);

#endif //CPP_GENERATE_GRAPH_H
