//
// Created by konrad on 11.11.18.
//

#ifndef CPP_GENERATE_GRAPH_H
#define CPP_GENERATE_GRAPH_H

#include <cstdint>
#include <riffle/BinMatrix.h>
#include <vector>

typedef std::vector<std::vector<std::vector<uint64_t>>> riffle_graph;

riffle_graph gen_graph(const std::vector<uint64_t> &seeds, const uint64_t g);

#endif // CPP_GENERATE_GRAPH_H
