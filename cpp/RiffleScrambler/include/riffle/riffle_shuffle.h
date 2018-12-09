//
// Created by konrad on 04.11.18.
//

#ifndef CPP_RIFFLE_SHUFFLE_H
#define CPP_RIFFLE_SHUFFLE_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <riffle/PRBG.h>

std::vector<uint64_t> riffle_shuffle(const uint64_t length,
                                     std::shared_ptr<PRBG> prbg);

#endif // CPP_RIFFLE_SHUFFLE_H
