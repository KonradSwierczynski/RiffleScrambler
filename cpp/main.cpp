#include <riffle/riffle_shuffle.h>
#include <riffle/riffle_permutation.h>
#include <riffle/generate_graph.h>
#include <riffle/evaluate_graph.h>

#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <string>
#include <stdlib.h>

#include <sstream>
#include <iomanip>

#include <memory>

#include <openssl/evp.h>

#include <riffle/HashFunctions/hashPRBG.h>


void riffle_shuffle_t(const uint64_t len) {

    auto ptr = std::make_shared<hashPRBG>("salt", 4);
    auto perm = riffle_shuffle(len, "test", ptr);
    std::cout << "Done!" << std::endl;
}


void evp_sha(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len) {

    EVP_MD_CTX *md_ctx;
    if((md_ctx = EVP_MD_CTX_create()) == NULL)
        return;

    if((1 != EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL)))
        return;

    if(1 != EVP_DigestUpdate(md_ctx, message, message_len))
        return;

    if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)
        return;

    if(1 != EVP_DigestFinal_ex(md_ctx, *digest, digest_len))
        return;

    EVP_MD_CTX_destroy(md_ctx);
}

void evp_test() {
    auto m = (unsigned char *)"test";
    size_t len = 5;
    unsigned char *digest;
    unsigned int digest_len;
    evp_sha(m, len, &digest, &digest_len);
    std::stringstream ss;
    for(int i = 0; i < EVP_MD_size(EVP_sha256()); i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)digest[i];
    }
    std::cout << "Hash: " << ss.str() << std::endl;
}

void sha_test() {
    std::string password = "test";
    std::cout << SHA256_DIGEST_LENGTH << std::endl;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char *)password.c_str(), password.size(), hash);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    std::cout << "Hash: " << ss.str() << std::endl;
}


void gen_g_t() {
    for(uint64_t g = 0; g < 20; g++) {
        uint64_t l = uint64_t(1) << g;
        std::cout << g << " " << l << std::endl;
        auto ptr = std::make_shared<hashPRBG>("salt", 4);
        auto perm = riffle_shuffle(l, "test", ptr);
        std::cout << "RF finished" << std::endl;
        auto grap = gen_graph(perm, g);
        std::cout << "Graph generated!" << std::endl;
    }
}

void test_eval(const uint64_t g, const uint64_t depth) {
    uint64_t l = uint64_t (1) << g;
    std::cout << g << " " << l << std::endl;
    auto prbg = std::make_shared<hashPRBG>("salt", 4);
    auto perm = riffle_shuffle(l, "test", prbg);
    std::cout << "RF finished" << std::endl;
    auto grap = gen_graph(perm, g);
    std::cout << "Graph generated!" << std::endl;
    auto result = eval_graph(grap, depth, g, "password");
    std::cout << "Eval done: " << result << std::endl;
}

void eval_range(const uint64_t max_g, const uint64_t depth) {
    for(uint64_t g = 0; g < max_g; g++) {
        test_eval(g, depth);
    }
}

int main() {
//    test_eval(20, 1);

    auto prbg = std::make_shared<hashPRBG>("salt", 4);
    auto res = riffle_shuffle(uint64_t (uint64_t (1) << 20), "salt", prbg);
    std::cout << "Perm size: " << res.size() << std::endl;
    std::cout << res[0] << " " << res[1] << " " << res[res.size() - 1] << std::endl;

//    gen_g_t();
//    eval_range(20, 3);

    return 0;
}

