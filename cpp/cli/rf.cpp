//
// Created by konrad on 13.12.18.
//

#include <riffle/riffle_scrambler.h>

#include "cxxopts.hpp"

#include <string>
#include <iostream>


int main(int argc, char **argv) {
    std::string password, salt, hash_func;
    uint64_t width, depth;

    try {
        cxxopts::Options options("RiffleScrambler", "Password hashing memory-hard function");

        options.add_options()
                ("p,password", "Password to hash", cxxopts::value<std::string>())
                ("s,salt", "Salt for the given password", cxxopts::value<std::string>())
                ("w,width", "Width of the graph", cxxopts::value<int>()->default_value("12"))
                ("d,depth", "Number of stack of the graph", cxxopts::value<int>()->default_value("2"))
                ("h,hash", "Hash function", cxxopts::value<std::string>()->default_value("sha256"))
        ;

        options.parse_positional({"password", "salt"});
        auto result = options.parse(argc, argv);

        password = result["password"].as<std::string>();
        salt = result["salt"].as<std::string>();
        width = static_cast<uint64_t>(result["width"].as<int>());
        depth = static_cast<uint64_t>(result["depth"].as<int>());
        hash_func = result["hash"].as<std::string>();

    } catch (const cxxopts::OptionException& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        exit(1);
    }

    std::cout << riffle_scrambler(password, salt, width, depth, hash_func) << std::endl;

    return 0;
}
