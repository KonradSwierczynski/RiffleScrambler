//
// Created by konrad on 11.11.18.
//

#ifndef CPP_BINMATRIX_H
#define CPP_BINMATRIX_H

#include <cstdint>
#include <vector>

class BinMatrix {
    std::vector<uint64_t> values;

  public:
    BinMatrix(const std::vector<uint64_t> values);

    bool getBit(const uint64_t column, const uint64_t row) const;
};

#endif // CPP_BINMATRIX_H
