//
// Created by konrad on 18.11.18.
//

//#include "riffle/PRBG.h"

#include <exception>
#include <fstream>
#include <string>

#include <fstream>
#include <iostream>

#include <riffle/PRBG.h>

using namespace std;

class readerPRBG : public PRBG {
    fstream fileStreamIn;
    uint64_t readBits;

  public:
    readerPRBG(string fileName) : readBits{0} {
        fileStreamIn = fstream(fileName, fstream::in);
    }

    bool getNextBit() override {
        char inChar;
        if (fileStreamIn >> noskipws >> inChar) {
            readBits++;
            return inChar == '1';
        }
        return false;
    }

    auto getReadBits() { return readBits; }
};
