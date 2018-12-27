//
// Created by konrad on 27.12.18.
//

#include "catch.hpp"
#include <riffle/riffle_scrambler.h>

#include <string>
#include <vector>
#include <iostream>


const std::string pwd = "password", salt = "salt";
const uint64_t g = 10, d = 4;
const std::string expected_hash = "e01334fe338711c5a4b73aff361ce38ed41f5ebfea4f83f5e7ed5fd77f2639c3";
const std::vector<unsigned char> expected_hash_raw = {224, 19, 52, 254, 51, 135, 17, 197, 164, 183, 58, 255, 54, 28, 227, 142, 212, 31, 94, 191, 234, 79, 131, 245, 231, 237, 95, 215, 127, 38, 57, 195};
const std::string expected_encoded = "$g=10$d=4$s=c2FsdA==$f=sha256$h=ZTAxMzM0ZmUzMzg3MTFjNWE0YjczYWZmMzYxY2UzOGVkNDFmNWViZmVhNGY4M2Y1ZTdlZDVmZDc3ZjI2MzljMw==";


TEST_CASE("Riffle Scrambler - String") {
    REQUIRE(riffle_scrambler(pwd, salt, g, d) == expected_hash);
}

TEST_CASE("Riffle Scrambler - Pointers") {
    REQUIRE(riffle_scrambler(pwd.c_str(), pwd.length(), salt.c_str(), salt.length(), g, d)
    == expected_hash);
}

TEST_CASE("Riffle Scrambler Raw - String") {
    const std::vector<unsigned char> hash_raw = riffle_scrambler_hash_raw(g, d, pwd, salt);

    REQUIRE(std::equal(hash_raw.begin(), hash_raw.end(), expected_hash_raw.begin()));
}

TEST_CASE("Riffle Scrambler Raw - Pointers") {
    const std::vector<unsigned char> hash_raw = riffle_scrambler_hash_raw(g, d, pwd.c_str(), pwd.length(),
            salt.c_str(), salt.length());

    REQUIRE(std::equal(hash_raw.begin(), hash_raw.end(), expected_hash_raw.begin()));
}

TEST_CASE("Riffle Scrambler Encoded - String") {
    const std::string encoded = riffle_scrambler_encoded(g, d, pwd, salt);

    REQUIRE(encoded == expected_encoded);
}

TEST_CASE("Riffle Scrambler Encoded - Pointers") {
    const std::string encoded = riffle_scrambler_encoded(g, d, pwd.c_str(), pwd.length(), salt.c_str(), salt.length());

    REQUIRE(encoded == expected_encoded);
}

TEST_CASE("Riffle Scrambler Verify - String") {
    REQUIRE(riffle_scrambler_verify(expected_encoded, pwd));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "another_pwd"));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "passwor"));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "passworD"));
    REQUIRE(riffle_scrambler_verify(expected_encoded, pwd));
}

TEST_CASE("Riffle Scrambler Verify - Pointers") {
    REQUIRE(riffle_scrambler_verify(expected_encoded, pwd));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "another_pwd", 11));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "passwor", 7));
    REQUIRE(!riffle_scrambler_verify(expected_encoded, "passworD", 8));
    REQUIRE(riffle_scrambler_verify(expected_encoded, pwd));
}