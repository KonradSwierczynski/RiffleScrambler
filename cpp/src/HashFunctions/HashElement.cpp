//
// Created by konrad on 15.11.18.
//

#include "../../include/HashFunctions/HashElement.h"
#include "../../include/HashFunctions/EVP_MD_Context_Adapter.h"


HashElement::HashElement() {}

HashElement::HashElement(const char * const message, const size_t message_len) {
    this->update((unsigned char *)message, message_len);
}

void HashElement::update(const HashElement &hashElement) {
    this->update(hashElement.md, hashElement.md_len);
}

void HashElement::update(const void * const message, const size_t message_len) {
    EVP_MD_Context_Adapter ctx;
    EVP_DigestInit_ex(ctx.getContext(), EVP_sha256(), nullptr);
    if(this->md_len) {
        EVP_DigestUpdate(ctx.getContext(), this->md, this->md_len);
    }
    EVP_DigestUpdate(ctx.getContext(), message, message_len);
    EVP_DigestFinal_ex(ctx.getContext(), this->md, &(this->md_len));
}

const unsigned char* HashElement::getDigest() const {
    return md;
}

unsigned int HashElement::getDigestLength() const {
    return md_len;
}

