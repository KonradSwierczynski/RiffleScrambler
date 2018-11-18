//
// Created by konrad on 15.11.18.
//

#ifndef CPP_HASHELEMENT_H
#define CPP_HASHELEMENT_H

#include <openssl/evp.h>
#include <string>

class HashElement {
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int md_len = 0;

public:

    HashElement();

    HashElement(const char * const message, const size_t message_len);

    void update(const HashElement &hashElement);

    void update(const void * const message, const size_t message_len);

    const unsigned char* getDigest() const;

    unsigned int getDigestLength() const;

    std::string toString() const;

};

#endif //CPP_HASHELEMENT_H
