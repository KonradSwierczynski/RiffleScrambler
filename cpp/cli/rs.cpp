//
// Created by konrad on 13.12.18.
//

#include <riffle/riffle_scrambler.h>

#include <riffle/hash_functions/hashPRBG.h>
#include <riffle/hash_functions/md_utils.h>
#include <riffle/hash_functions/HashResult.h>
#include <riffle/evaluate_graph.h>
#include <riffle/generate_graph.h>
#include <riffle/riffle_shuffle.h>

#include <riffle/encoding.h>

#include "cxxopts.hpp"

#include <string>
#include <iostream>


const HashResult _riffle_scrambler(const uint64_t garlic,
                            const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
                            const void *salt, const size_t saltlen_bytes, const std::string hash_func) {
    const MD_Wrapper wrapper = get_md_by_name(hash_func);
    const uint64_t size = uint64_t(1) << garlic;
    const auto prbg = std::make_shared<hashPRBG>(salt, saltlen_bytes);
    const auto perm = riffle_shuffle(size, prbg);
    const auto graph = gen_graph(perm, garlic);
    return eval_graph(graph, depth, garlic, pwd, pwdlen_bytes, wrapper);
}


int main(int argc, char **argv) {
    std::string password, salt, hash_func;
    uint64_t width, depth;

    try {
        cxxopts::Options options("RiffleScrambler  Password is read from stdin", "Password hashing memory-hard function");
        options.positional_help("[optional args]").show_positional_help();

        options.add_options()
                ("s,salt", "Salt for the given password", cxxopts::value<std::string>())
                ("w,width", "Width of the graph", cxxopts::value<int>()->default_value("12"))
                ("d,depth", "Number of stacks of the graph", cxxopts::value<int>()->default_value("2"))
                ("f,func", "Internal hash function", cxxopts::value<std::string>()->default_value("sha256"))
                ("h,help", "Print help")
        ;

        options.parse_positional({"password", "salt"});
        auto result = options.parse(argc, argv);

        if (result.count("help"))
        {
            std::cout << options.help({"", "Group"}) << std::endl;
            exit(0);
        }

        salt = result["salt"].as<std::string>();
        width = static_cast<uint64_t>(result["width"].as<int>());
        depth = static_cast<uint64_t>(result["depth"].as<int>());
        hash_func = result["func"].as<std::string>();
        std::cin >> password;

    } catch (const cxxopts::OptionException& e) {
        std::cerr << "Error parsing options: " << e.what() << std::endl;
        exit(1);
    } catch (const std::domain_error& e) {
        std::cerr << "Wrong argument type: " << e.what() << std::endl;
        exit(2);
    }

    const auto hashResult = _riffle_scrambler(width, depth, password.c_str(), password.size(), salt.c_str(), salt.size(), hash_func);
    const auto encoded = encode_string(width, depth, salt.c_str(), salt.length(), hash_func, hashResult);

    std::cout << "Graph width:\t" << width << std::endl;
    std::cout << "Graph depth:\t" << depth << std::endl;
    std::cout << "Hash:       \t" << hashResult.toString() << std::endl;
    std::cout << "Encoded:    \t" << encoded << std::endl;

    return 0;
}
