//
// Created by konrad on 21.12.18.
//

#include "riffle/hash_functions/HashResult.h"

#include <sstream>
#include <iomanip>


std::string HashResult::toString() const {
    std::stringstream ss;
    for (int i = 0; i < this->md_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)this->md[i];
    }
    return ss.str();
}

HashResult::operator std::string() const {
    return this->toString();
}