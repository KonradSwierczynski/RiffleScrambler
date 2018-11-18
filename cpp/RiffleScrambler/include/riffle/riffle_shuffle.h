//
// Created by konrad on 04.11.18.
//

#ifndef CPP_RIFFLE_SHUFFLE_H
#define CPP_RIFFLE_SHUFFLE_H

#include <vector>
#include <string>
#include <cstdint>
#include <memory>

#include <riffle/PRBG.h>


std::vector<uint64_t> riffle_shuffle(const uint64_t length, const char *salt, std::shared_ptr<PRBG> prbg);

#endif //CPP_RIFFLE_SHUFFLE_H
