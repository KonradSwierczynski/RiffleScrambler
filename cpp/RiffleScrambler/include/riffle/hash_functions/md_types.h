//
// Created by konrad on 28.11.18.
//

#ifndef CPP_MD_TYPE_H
#define CPP_MD_TYPE_H

#include <openssl/evp.h>

struct MD_Base {
    virtual const size_t get_size() const = 0;
    virtual const EVP_MD *get_md() const = 0;
};

template <typename T> struct MD_Type : public MD_Base {
    const size_t get_size() const override { return T::size; }

    const EVP_MD *get_md() const override { return T::get_evp(); }
};

struct MD_sha224 {
    static constexpr const size_t size = 224 / 8;
    static constexpr const auto get_evp = EVP_sha224;
};

struct MD_sha256 {
    static constexpr const size_t size = 256 / 8;
    static constexpr const auto get_evp = EVP_sha256;
};

struct MD_sha384 {
    static constexpr const size_t size = 384 / 8;
    static constexpr const auto get_evp = EVP_sha384;
};

struct MD_sha512 {
    static constexpr const size_t size = 512 / 8;
    static constexpr const auto get_evp = EVP_sha512;
};

struct MD_sha1 {
    static constexpr const size_t size = 160 / 8;
    static constexpr const auto get_evp = EVP_sha1;
};

struct MD_md5 {
    static constexpr const size_t size = 128 / 8;
    static constexpr const auto get_evp = EVP_md5;
};

struct MD_mdc2 {
    static constexpr const size_t size = 128 / 8;
    static constexpr const auto get_evp = EVP_mdc2;
};

struct MD_ripemd160 {
    static constexpr const size_t size = 160 / 8;
    static constexpr const auto get_evp = EVP_ripemd160;
};

struct MD_blake2s256 {
    static constexpr const size_t size = 256 / 8;
    static constexpr const auto get_evp = EVP_blake2s256;
};

struct MD_blake2s512 {
    static constexpr const size_t size = 512 / 8;
    static constexpr const auto get_evp = EVP_blake2b512;
};

#endif // CPP_MD_TYPE_H
