#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>
#include <riffle/riffle_permutation.h>
#include <riffle/riffle_scrambler.h>
#include <riffle/riffle_shuffle.h>

#include <iostream>
#include <openssl/sha.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include <iomanip>
#include <sstream>

#include <memory>

#include <openssl/evp.h>

#include <riffle/hash_functions/hashPRBG.h>

void perm_test(std::string password, std::string salt, uint64_t g, uint64_t d) {
    auto prbg = std::make_shared<hashPRBG>(salt.c_str(), salt.length());
    auto res = riffle_shuffle(uint64_t(uint64_t(1) << g), prbg);
    std::cout << "Perm size: " << res.size() << std::endl;
    std::cout << res[0] << " " << res[1] << " " << res[res.size() - 1]
              << std::endl;
}

void rs_test(std::string password, std::string salt, uint64_t max_g,
             uint64_t d) {
    for (uint64_t i = 0; i <= max_g; i++) {
        std::cout << ">> G = " << i << std::endl;
        auto hash = riffle_scrambler(password, salt, i, d);
        std::cout << "Hash = " << hash << std::endl;
        std::cerr << i << " " << hash << std::endl;
    }
}

int main() {
    std::cout << "Hash: " << riffle_scrambler("test", "salt", 12, 4, "sha256")
              << std::endl;

    //    rs_test("test", "salt", 20, 5);

    std::cout << std::endl << "End of main" << std::endl;
    return 0;
}
