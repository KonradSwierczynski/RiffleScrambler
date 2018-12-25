//
// Created by konrad on 23.12.18.
//

#include <riffle/encoding.h>
#include <riffle/base64.h>

#include <sstream>
#include <array>
#include <algorithm>


const std::string GARLIC_PREFIX = "$g=";
const std::string DEPTH_PREFIX = "$d=";
const std::string SALT_PREFIX = "$s=";
const std::string HASH_FUNC_PREFIX = "$f=";
const std::string HASH_PREFIX = "$h=";
const size_t PREFIX_LEN = 3;


std::string get_slice(const std::string &str, const size_t start, const size_t end) {
    return str.substr(start, end - start);
}

std::string get_slice(const std::string &str, const size_t start) {
    return str.substr(start);
}

std::string encode_string(const uint64_t garlic, const uint64_t depth,
        const void *salt, const size_t saltlen_bytes,
        const std::string &hash_func, const HashResult hashResult) {

    std::stringstream ss;
    std::string hash{hashResult};

    ss << GARLIC_PREFIX << garlic
    << DEPTH_PREFIX << depth
    << SALT_PREFIX << base64_encode((unsigned char *)salt, saltlen_bytes)
    << HASH_FUNC_PREFIX << hash_func
    << HASH_PREFIX << base64_encode((unsigned char *)hash.c_str(), hash.length());

    return ss.str();
}

// Encoded string example: $g=123$d=123213$s=j09j293j$h=oijf92j
const RiffleScramberContext decode_string(const std::string &encoded) {
    size_t garlic_index, depth_index, salt_index, hash_func_index, hash_index;

    garlic_index = encoded.find(GARLIC_PREFIX);
    depth_index = encoded.find(DEPTH_PREFIX);
    salt_index = encoded.find(SALT_PREFIX);
    hash_func_index = encoded.find(HASH_FUNC_PREFIX);
    hash_index = encoded.find(HASH_PREFIX);

    const std::array values = {garlic_index, depth_index, salt_index, hash_func_index, hash_index};

    if(std::any_of(values.begin(), values.end(),
            [](const size_t i){ return i == std::string::npos;})) {
//        throw XXXX;
    }

    std::string garlic_str, depth_str, salt_str_base64, hash_func_str, hash_str_base64;

    garlic_str = get_slice(encoded, garlic_index + PREFIX_LEN, depth_index);
    depth_str = get_slice(encoded, depth_index + PREFIX_LEN, salt_index);
    salt_str_base64 = get_slice(encoded, salt_index + PREFIX_LEN, hash_func_index);
    hash_func_str = get_slice(encoded, hash_func_index + PREFIX_LEN, hash_index);
    hash_str_base64 = get_slice(encoded, hash_index);

    uint64_t garlic, depth;
    garlic = std::stoull(garlic_str);
    depth = std::stoull(depth_str);

    std::string salt, hash;
    salt = base64_decode(salt_str_base64);
    hash = base64_decode(hash_str_base64);


    return {garlic, depth, salt, hash, hash_func_str};
}
