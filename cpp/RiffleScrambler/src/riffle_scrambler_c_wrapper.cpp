//
// Created by konrad on 07.01.19.
//

#include <riffle/riffle_scrambler_c.h>

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/hash_functions/md_utils.h>
#include <riffle/hash_functions/HashResult.h>
#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>
#include <riffle/riffle_shuffle.h>

#include <string.h>


void _riffle_scrambler(void *out, const size_t outlen, const uint64_t garlic,
                            const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
                            const void *salt, const size_t saltlen_bytes) {
    const MD_Wrapper wrapper = get_md_by_name("sha256");
    const uint64_t size = uint64_t(1) << garlic;
    const auto prbg = std::make_shared<hashPRBG>(salt, saltlen_bytes);
    const auto perm = riffle_shuffle(size, prbg);
    const auto graph = gen_graph(perm, garlic);
    const HashResult result =  eval_graph(graph, depth, garlic, pwd, pwdlen_bytes, wrapper);

    memcpy(out, result.md.data(), outlen);
}


extern "C" {

int riffle_scrambler(void *hash, const size_t hashlen, const void *pwd,
        const size_t pwdlen_bytes, const void *salt, const size_t saltlen_bytes,
        const uint64_t t_cost, const uint64_t m_cost) {

    if(hashlen < RIFFLE_MIN_OUTLEN) {
        return RIFFLE_OUTPUT_TOO_SHORT;
    }

    if(hashlen > RIFFLE_MAX_OUTLEN) {
        return RIFFLE_OUTPUT_TOO_LONG;
    }

    if(hash == NULL) {
        return RIFFLE_OUTPUT_PTR_NULL;
    }

    _riffle_scrambler(hash, hashlen, m_cost, t_cost, pwd, pwdlen_bytes, salt, saltlen_bytes);

    return RIFFLE_SCRAMBLER_OK;
}

}
