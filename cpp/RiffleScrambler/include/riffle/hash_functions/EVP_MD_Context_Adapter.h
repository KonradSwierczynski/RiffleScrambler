//
// Created by konrad on 15.11.18.
//

#ifndef CPP_EVP_MD_CONTEXT_ADAPTER_H
#define CPP_EVP_MD_CONTEXT_ADAPTER_H

#include <openssl/evp.h>

class EVP_MD_Context_Adapter {
    EVP_MD_CTX *ctx;

  public:
    EVP_MD_Context_Adapter();

    EVP_MD_CTX *getContext() const;

    ~EVP_MD_Context_Adapter();
};

#endif // CPP_EVP_MD_CONTEXT_ADAPTER_H
