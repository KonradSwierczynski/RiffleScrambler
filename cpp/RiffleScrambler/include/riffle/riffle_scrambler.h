//
// Created by konrad on 19.11.18.
//

#ifndef CPP_RIFFLE_SCRAMBLER_H
#define CPP_RIFFLE_SCRAMBLER_H

#include <string>

std::string riffle_scrambler(const std::string password, const std::string salt,
        const uint64_t garlic, const uint64_t depth, const std::string hash_func="sha256");

#endif //CPP_RIFFLE_SCRAMBLER_H
