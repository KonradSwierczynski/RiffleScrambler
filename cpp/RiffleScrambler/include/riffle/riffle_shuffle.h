//
// Created by konrad on 04.11.18.
//

#ifndef CPP_RIFFLE_SHUFFLE_H
#define CPP_RIFFLE_SHUFFLE_H

#include <vector>
#include <string>
#include <cstdint>

std::vector<uint64_t> riffle_shuffle(const uint64_t length, const char *salt);

#endif //CPP_RIFFLE_SHUFFLE_H
