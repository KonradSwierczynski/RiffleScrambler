//
// Created by konrad on 15.11.18.
//

#include <riffle/hash_functions/EVP_MD_Context_Adapter.h>

EVP_MD_Context_Adapter::EVP_MD_Context_Adapter() {
    if ((this->ctx = EVP_MD_CTX_create()) == NULL) {
        return;
    }
}

EVP_MD_CTX *EVP_MD_Context_Adapter::getContext() const { return this->ctx; }

EVP_MD_Context_Adapter::~EVP_MD_Context_Adapter() {
    EVP_MD_CTX_destroy(this->ctx);
}
