#include <riffle/riffle_scrambler.h>
#include <riffle/base64.h>

#include <iostream>
#include <string>


int main() {
    std::string pwd = "test123!?", salt = "salt";
    uint64_t g = 12, d = 2;

    const std::string hash = riffle_scrambler_encoded(g, d, pwd, salt);

    std::cout << hash << std::endl;



    std::cout << std::endl << "End of main" << std::endl;
    return 0;
}
