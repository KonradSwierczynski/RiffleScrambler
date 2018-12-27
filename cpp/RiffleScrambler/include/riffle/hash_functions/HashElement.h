//
// Created by konrad on 15.11.18.
//

#ifndef CPP_HASHELEMENT_H
#define CPP_HASHELEMENT_H

#include <openssl/evp.h>
#include <vector>

#include <riffle/hash_functions/EVP_MD_Context_Adapter.h>
#include <riffle/hash_functions/md_types.h>
#include <riffle/hash_functions/message_digests.h>
#include <riffle/hash_functions/HashResult.h>


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

    const HashResult finalize() const;
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

const HashResult HashElement::finalize() const {
    return HashResult{this->md, this->md_len};
}

#endif // CPP_HASHELEMENT_H
