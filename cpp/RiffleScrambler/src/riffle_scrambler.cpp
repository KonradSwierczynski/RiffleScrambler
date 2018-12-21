//
// Created by konrad on 19.11.18.
//

#include <riffle/riffle_scrambler.h>

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/hash_functions/md_utils.h>
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


/*

std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
                            const uint8_t *pwd, const size_t pwdlen_bytes,
                            const uint8_t *salt, const size_t saltlen_bytes) {

}

std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic,
                            const uint64_t depth, const uint8_t *pwd, const size_t pwdlen_bytes,
                            const uint8_t *salt, const size_t saltlen_bytes) { }

*/