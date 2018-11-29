//
// Created by konrad on 11.11.18.
//

#ifndef CPP_EVALUATE_GRAPH_H
#define CPP_EVALUATE_GRAPH_H

#include <vector>
#include <cstdint>
#include <string>

#include <riffle/generate_graph.h>
#include <riffle/HashFunctions/message_digests.h>


std::string eval_graph(const riffle_graph edges, const uint64_t depth, const uint64_t g, const std::string value, const MD_Wrapper wrapper);

#endif //CPP_EVALUATE_GRAPH_H
