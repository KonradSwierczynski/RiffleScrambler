//
// Created by konrad on 11.11.18.
//

//#include "../../include/BinMatrix.h"
#include <riffle/BinMatrix.h>

BinMatrix::BinMatrix(const std::vector<uint64_t> values) {
    this->values = values;
}

bool BinMatrix::getBit(const uint64_t column, const uint64_t row) const {
    return (this->values[column] >> row) & 1;
}
