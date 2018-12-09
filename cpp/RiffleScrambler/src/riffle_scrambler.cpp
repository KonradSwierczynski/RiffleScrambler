//
// Created by konrad on 19.11.18.
//

#include <riffle/riffle_scrambler.h>

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/hash_functions/md__utils.h>
#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>
#include <riffle/riffle_shuffle.h>

#include <memory>

std::string riffle_scrambler(const std::string password, const std::string salt,
                             const uint64_t garlic, const uint64_t depth,
                             const std::string hash_func) {
    const MD_Wrapper wrapper = get_md_by_name(hash_func);
    const uint64_t size = uint64_t(1) << garlic;
    const auto prbg = std::make_shared<hashPRBG>(salt.c_str(), salt.size());
    const auto perm = riffle_shuffle(size, prbg);
    const auto graph = gen_graph(perm, garlic);
    auto hash = eval_graph(graph, depth, garlic, password, wrapper);
    return hash;
}
