#include <riffle/riffle_scrambler.h>
#include <riffle/base64.h>

#include <iostream>
#include <string>


int main() {
    std::string pwd = "test123!?", salt = "salt";
    uint64_t g = 16, d = 10;

    const auto hash = riffle_scrambler(pwd, salt, g, d);
//    const auto hash2 = riffle_scrambler(pwd.c_str(), pwd.length(), salt.c_str(), salt.length(), g, d);
//    std::cout << "1. Hash: " << hash << " " << hash2
//              << "\t" << std::endl << "base64: " << base64_encode((unsigned char *)hash.c_str(), hash.length())
//              << "\t" << std::endl;
//
//    const std::string encoded = riffle_scrambler_encoded(g, d, pwd, salt);
//    std::cout << "2. Encoded: " << encoded << std::endl;
//
//    const auto result = riffle_scrambler_verify(encoded, "test123!?");
//
//    std::cout << "3. Verify res: " << result << std::endl;



    std::cout << std::endl << "End of main" << std::endl;
    return 0;
}
