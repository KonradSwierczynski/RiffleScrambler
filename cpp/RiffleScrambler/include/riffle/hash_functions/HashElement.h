//
// Created by konrad on 15.11.18.
//

#ifndef CPP_HASHELEMENT_H
#define CPP_HASHELEMENT_H

#include <iomanip>
#include <openssl/evp.h>
#include <sstream>
#include <string>
#include <vector>

#include <riffle/hash_functions/EVP_MD_Context_Adapter.h>
#include <riffle/hash_functions/md_types.h>
#include <riffle/hash_functions/message_digests.h>

class HashElement {
    const MD_Wrapper wrapper;
    std::vector<unsigned char> md;
    unsigned int md_len = 0;

  public:
    HashElement(const MD_Wrapper wrapper);

    HashElement(const char *const message, const size_t message_len,
                const MD_Wrapper);

    void update(const HashElement &hashElement);

    void update(const void *const message, const size_t message_len);

    const unsigned char *getDigest() const;

    unsigned int getDigestLength() const;

    std::string toString() const;
};

HashElement::HashElement(const MD_Wrapper wrapper)
    : wrapper{wrapper}, md(wrapper.get_size()) {}

HashElement::HashElement(const char *const message, const size_t message_len,
                         const MD_Wrapper wrapper)
    : wrapper{wrapper} {
    this->update((unsigned char *)message, message_len);
}

void HashElement::update(const HashElement &hashElement) {
    this->update(hashElement.md.data(), hashElement.md_len);
}

void HashElement::update(const void *const message, const size_t message_len) {
    EVP_MD_Context_Adapter ctx;
    EVP_DigestInit_ex(ctx.getContext(), wrapper.get_md(), nullptr);
    if (this->md_len) {
        EVP_DigestUpdate(ctx.getContext(), this->md.data(), this->md_len);
    }
    EVP_DigestUpdate(ctx.getContext(), message, message_len);
    EVP_DigestFinal_ex(ctx.getContext(), this->md.data(), &(this->md_len));
}

const unsigned char *HashElement::getDigest() const { return md.data(); }

unsigned int HashElement::getDigestLength() const { return md_len; }

std::string HashElement::toString() const {
    std::stringstream ss;
    for (int i = 0; i < this->md_len; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)this->md[i];
    }
    return ss.str();
}

#endif // CPP_HASHELEMENT_H
