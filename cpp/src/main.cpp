#include "../include/riffle_shuffle.h"
#include "../include/riffle_permutation.h"
#include "../include/generate_graph.h"

#include <iostream>
#include <vector>
#include <openssl/sha.h>
#include <string>
#include <stdlib.h>

#include <sstream>
#include <iomanip>

#include <openssl/evp.h>

#include "../include/evaluate_graph.h"

void riffle_shuffle_t(const uint64_t len) {
    auto perm = riffle_shuffle(len, "test");
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
    for(uint64_t g = 8; g > 0; g--) {
        uint64_t l = 1 << g;
        std::cout << g << " " << l << std::endl;
        auto perm = riffle_shuffle(l, "test");
        std::cout << "RF finished" << std::endl;
        auto grap = gen_graph(perm, g);
        std::cout << "Graph generated!" << std::endl;
    }
}

void test_eval() {
    const uint64_t g = 12, depth = 10;
    uint64_t l = 1 << g;
    std::cout << g << " " << l << std::endl;
    auto perm = riffle_shuffle(l, "test");
    std::cout << "RF finished" << std::endl;
    auto grap = gen_graph(perm, g);
    std::cout << "Graph generated!" << std::endl;
    auto result = eval_graph(grap, depth, g, "testtestetestesttestestestestestestestestestestestestestestest");
    std::cout << "Eval done: " << result << std::endl;
}

int main() {
//    gen_g_t();
//    sha_test();
//    evp_test();
//    test_eval();
    for(uint64_t i = 0; i < 18; i++) {
        std::cout << "RF " << i << std::endl;
        riffle_shuffle_t(1 << i);
    }


    return 0;
}

