//
// Created by konrad on 19.11.18.
//

#include <riffle/riffle_scrambler.h>

#include <riffle/riffle_shuffle.h>
#include <riffle/generate_graph.h>
#include <riffle/evaluate_graph.h>
#include <riffle/HashFunctions/hashPRBG.h>

#include <memory>

std::string riffle_scrambler(const std::string password, const std::string salt,
                             const uint64_t garlic, const uint64_t depth) {
    uint64_t size = uint64_t (1) << garlic;
    auto prbg = std::make_shared<hashPRBG>(salt.c_str(), salt.size());
    const auto perm = riffle_shuffle(size, prbg);
    const auto graph = gen_graph(perm, garlic);
    auto hash = eval_graph(graph, depth, garlic, password);
    return hash;
}

