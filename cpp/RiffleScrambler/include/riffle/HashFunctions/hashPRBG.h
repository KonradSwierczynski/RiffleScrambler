//
// Created by konrad on 16.11.18.
//

#ifndef CPP_HASHPRBG_H
#define CPP_HASHPRBG_H

#include <riffle/HashFunctions/EVP_MD_Context_Adapter.h>
#include <riffle/PRBG.h>

class hashPRBG : public PRBG {
    EVP_MD_Context_Adapter ctx;
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;
    unsigned int position = 0;

    void generateNewBuffor(const void * const message, const size_t message_len);

public:
    hashPRBG(const void * const message, const size_t message_len);
    bool getNextBit();
};



#endif //CPP_HASHPRBG_H
