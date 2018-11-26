//
// Created by konrad on 18.11.18.
//

//#include "riffle/PRBG.h"

#include <fstream>
#include <string>
#include <exception>

#include <iostream>
#include <fstream>

#include <riffle/PRBG.h>

using namespace std;


class readerPRBG: public PRBG {
    fstream fileStreamIn;
    uint64_t readBits;
public:
    readerPRBG(string fileName): readBits{0} {
        fileStreamIn = fstream(fileName, fstream::in);
    }

    bool getNextBit() override {
        char inChar;
        if( fileStreamIn >> noskipws >> inChar) {
            readBits++;
            return inChar == '1';
        }
        return false;
    }


    auto getReadBits() {
        return readBits;
    }
};

