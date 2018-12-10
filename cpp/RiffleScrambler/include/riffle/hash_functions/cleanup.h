//
// Created by konrad on 10.12.18.
//

#ifndef CPP_EVP_CLEANUP_H
#define CPP_EVP_CLEANUP_H

#include <openssl/evp.h>


void cleanup() {
    EVP_cleanup();
}

#endif //CPP_EVP_CLEANUP_H
