//
// Created by konrad on 12.11.18.
//

#include "catch.hpp"

#include <vector>
#include <memory>
#include <iostream>

#include <riffle/BinMatrix.h>
#include <riffle/riffle_permutation.h>
#include <riffle/riffle_shuffle.h>
#include <riffle/riffle_scrambler.h>


#include <riffle/PRBG.h>

#include <fstream>
#include <string>
#include <exception>

using namespace std;

TEST_CASE("main") {
    for(int g = 0; g <= 16; g++) {
        cerr << g << "\t" << riffle_scrambler("test", "salt", g, 1) << endl;
    }

}


