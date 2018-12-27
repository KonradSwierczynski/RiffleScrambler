//
// Created by konrad on 19.11.18.
//

#ifndef CPP_RIFFLE_SCRAMBLER_H
#define CPP_RIFFLE_SCRAMBLER_H


#include <string>
#include <vector>


std::string riffle_scrambler(const std::string password, const std::string salt,
                             const uint64_t garlic, const uint64_t depth,
                             const std::string hash_func = "sha256");


std::string riffle_scrambler(const void *const password, const size_t pwdlen_bytes,
                            const void *const salt, const size_t saltlen_bytes,
                            const uint64_t garlic, const uint64_t depth,
                            const std::string hash_func="sha256");


std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic, const uint64_t depth,
        const std::string password, const std::string salt,
        const std::string hash_func="sha256");


std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic,
         const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
         const void *salt, const size_t saltlen_bytes, const std::string hash_func="sha256");



std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
        const void *pwd, const size_t pwdlen_bytes,
        const void *salt, const size_t saltlen_bytes, const std::string hash_func="sha256");


std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
        const std::string pwd,
        const std::string salt, const std::string hash_func="sha256");


bool riffle_scrambler_verify(const std::string encoded, const std::string pwd);


bool riffle_scrambler_verify(const std::string encoded, const void *pwd, const size_t pwd_len);



#endif // CPP_RIFFLE_SCRAMBLER_H
