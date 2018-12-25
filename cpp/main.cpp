#include <riffle/riffle_scrambler.h>
#include <riffle/base64.h>

#include <iostream>
#include <string>


int main() {
    const auto hash = riffle_scrambler("test", "salt", 12, 4, "sha256");
    std::cout << "Hash: " << hash
              << std::endl << "base64: " << base64_encode((unsigned char *)hash.c_str(), hash.length())
              << std::endl;

    const std::string encoded = riffle_scrambler_encoded(12, 4, "test", "salt") ;
    std::cout << "Encoded: " << encoded << std::endl;



    std::cout << std::endl << "End of main" << std::endl;
    return 0;
}
