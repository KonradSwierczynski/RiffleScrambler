//
// Created by konrad on 25.11.18.
//

#include "catch.hpp"

#include <riffle/riffle_scrambler.h>

#include <string>

using namespace std;


TEST_CASE("Riffle scrambler - check known values", "[rf][slow]") {
    const string password = "some password", salt = "SALT";

    SECTION("g = 4, depth = 10") {
        const auto hash = riffle_scrambler(password, salt, 4, 10);
        const auto expected_hash = "f84414c1450f2b4ac7d4ef207e97b2b9db4c3f48229e37b79bcd1df17831bbee";

        REQUIRE(hash == expected_hash);
    }

//    SECTION("g = 8, depth = 8") {
//        const auto hash = riffle_scrambler(password, salt, 8, 8);
//        const auto expected_hash = "607f19a781a2ce25eedaeca533212232921157f9c19842ef76a728867d87e468";
//
//        REQUIRE(hash == expected_hash);
//    }
//
//    SECTION("g = 14, depth = 4") {
//        const auto hash = riffle_scrambler(password, salt, 14, 4);
//        const auto expected_hash = "4a977bbb417589aa09776de9f1813c3c4371c88f89c3ce5ffa0e44f050da911d";
//
//        REQUIRE(hash == expected_hash);
//    }
//
//    SECTION("g = 16, depth = 1") {
//        const auto hash = riffle_scrambler(password, salt, 16, 1);
//        const auto expected_hash = "3f503d180d82232ba68ff8e499e54407463f516d80f5fd25aede6eb3b16778fb";
//
//        REQUIRE(hash == expected_hash);
//    }
//
//    SECTION("Big hash g = 18, depth = 1") {
//        const auto hash = riffle_scrambler(password, salt, 18, 1);
//        const auto expected_hash = "09c62945135a7539ee6d33ea6666dbc147668ba6dbf64ad81853f6eeb1160117";
//
//        REQUIRE(hash == expected_hash);
//    }
}

TEST_CASE("Riffle scrambler - same output", "[rf]") {
    const string password = "password", salt = "salt";
    for(uint64_t g = 1; g < 10; g++) {
        for(uint64_t depth = 1; depth < 4; depth++) {
            const auto hash1 = riffle_scrambler(password, salt, g, depth);
            const auto hash2 = riffle_scrambler(password, salt, g, depth);

            REQUIRE(hash1 == hash2);
        }
    }
}

