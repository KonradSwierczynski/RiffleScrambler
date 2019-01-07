//
// Created by konrad on 19.11.18.
//

#include <riffle/riffle_scrambler.h>

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/hash_functions/md_utils.h>
#include <riffle/hash_functions/HashResult.h>
#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>
#include <riffle/riffle_shuffle.h>

#include <riffle/encoding.h>


/**
 * Hashowanie hasła za pomocą RiffleScrambler
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający ilość iteracji
 * @param pwd Wskaźnik na hasło
 * @param pwdlen_bytes Długość hasła w bajtach
 * @param salt Wskaźnik na sól
 * @param saltlen_bytes Długość soli w bajtach
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia
 * @return Obiekt zawerający hash hasła
 */
const HashResult _riffle_scrambler(const uint64_t garlic,
                            const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
                            const void *salt, const size_t saltlen_bytes, const std::string hash_func) {
    // Tworzenie instancji kryptograficznej funkcji skrótu
    const MD_Wrapper wrapper = get_md_by_name(hash_func);
    // Obliczenie szerokości grafu N = 2^g
    const uint64_t size = uint64_t(1) << garlic;
    // Tworzenie generatora bitów pseudolosowych na podstawie soli
    const auto prbg = std::make_shared<hashPRBG>(salt, saltlen_bytes);
    // Obliczanie permutacji dla podanego rozmiaru i generatora
    const auto perm = riffle_shuffle(size, prbg);
    // Tworzenie grafu RSG
    const auto graph = gen_graph(perm, garlic);
    // Obliczenie na wygenerowanym grafie hasha hasła
    return eval_graph(graph, depth, garlic, pwd, pwdlen_bytes, wrapper);
}



std::string riffle_scrambler(const std::string password, const std::string salt,
                             const uint64_t garlic, const uint64_t depth,
                             const std::string hash_func) {
    return _riffle_scrambler(garlic, depth, password.c_str(), password.size(), salt.c_str(), salt.size(), hash_func).toString();
}


std::string riffle_scrambler(const void *const password, const size_t pwdlen_bytes,
                            const void *const salt, const size_t saltlen_bytes,
                            const uint64_t garlic, const uint64_t depth,
                            const std::string hash_func) {
    return _riffle_scrambler(garlic, depth, password, pwdlen_bytes, salt, saltlen_bytes, hash_func).toString();
}

std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic, const uint64_t depth,
                            const std::string password, const std::string salt,
                            const std::string hash_func) {
    return _riffle_scrambler(garlic, depth, password.c_str(), password.size(), salt.c_str(), salt.size(), hash_func).md;
}

std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic,
                            const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
                            const void *salt, const size_t saltlen_bytes, const std::string hash_func) {
    return _riffle_scrambler(garlic, depth, pwd, pwdlen_bytes, salt, saltlen_bytes, hash_func).md;
}


std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
                            const void *pwd, const size_t pwdlen_bytes,
                            const void *salt, const size_t saltlen_bytes, const std::string hash_func) {
    const auto hashResult = _riffle_scrambler(garlic, depth, pwd, pwdlen_bytes, salt, saltlen_bytes, hash_func);
    return encode_string(garlic, depth, salt, saltlen_bytes, hash_func, hashResult);
}

std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
                            const std::string pwd,
                            const std::string salt, const std::string hash_func) {
    const auto hashResult = _riffle_scrambler(garlic, depth, pwd.c_str(), pwd.size(), salt.c_str(), salt.size(), hash_func);
    return encode_string(garlic, depth, salt.c_str(), salt.length(), hash_func, hashResult);
}

bool riffle_scrambler_verify(const std::string encoded, const std::string pwd) {
    const RiffleScramberContext rs_ctx = decode_string(encoded);

    const auto result = _riffle_scrambler(rs_ctx.garlic, rs_ctx.depth, pwd.c_str(), pwd.size(),
            rs_ctx.salt.c_str(), rs_ctx.salt.size(), rs_ctx.md);
    return result.toString() == rs_ctx.hash;
}

bool riffle_scrambler_verify(const std::string encoded, const void *pwd, const size_t pwd_len) {
    const RiffleScramberContext rs_ctx = decode_string(encoded);

    const auto result = _riffle_scrambler(rs_ctx.garlic, rs_ctx.depth, pwd, pwd_len,
            rs_ctx.salt.c_str(), rs_ctx.salt.size(), rs_ctx.md);

    return result.toString() == rs_ctx.hash;
}

