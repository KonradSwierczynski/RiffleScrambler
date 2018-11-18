//
// Created by konrad on 11.11.18.
//

#ifndef CPP_EVALUATE_GRAPH_H
#define CPP_EVALUATE_GRAPH_H

#include <vector>
#include <cstdint>
#include <string>

std::string eval_graph(const std::vector<std::vector<std::vector<uint64_t>>> edges, const uint64_t depth, const uint64_t g, const std::string value);

#endif //CPP_EVALUATE_GRAPH_H
