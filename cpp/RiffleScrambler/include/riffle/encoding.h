//
// Created by konrad on 23.12.18.
//

#ifndef CPP_ENCODING_H
#define CPP_ENCODING_H

#include <riffle/hash_functions/HashResult.h>

#include <string>


struct RiffleScramberContext {
    uint64_t garlic;
    uint64_t depth;
    std::string salt;
    std::string hash;
    std::string md;
};

std::string encode_string(const uint64_t garlic, const uint64_t depth,
        const void *salt, const size_t saltlen_bytes,
        const std::string &hash_func, const HashResult hashResult);


const RiffleScramberContext decode_string(const std::string encoded);


#endif //CPP_ENCODING_H
