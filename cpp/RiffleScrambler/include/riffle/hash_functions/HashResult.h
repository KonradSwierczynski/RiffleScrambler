//
// Created by konrad on 21.12.18.
//

#ifndef CPP_HASHRESULT_H
#define CPP_HASHRESULT_H

#include <string>
#include <vector>

struct HashResult {
    std::vector<unsigned char> md;
    unsigned int md_len;

    std::string toString() const;
    operator std::string() const;
};


#endif //CPP_HASHRESULT_H
