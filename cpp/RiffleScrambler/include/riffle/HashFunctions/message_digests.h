//
// Created by konrad on 29.11.18.
//

#ifndef CPP_MESSAGE_DIGESTS_H
#define CPP_MESSAGE_DIGESTS_H

#include <riffle/HashFunctions/md_types.h>

#include <memory>

struct MD_Wrapper {
  private:
    std::shared_ptr<MD_Base> md_t;

  public:
    template <typename MD_T>
    explicit MD_Wrapper(MD_T &&) : md_t{std::make_shared<MD_T>()} {}

    size_t get_size() const { return md_t->get_size(); }

    const EVP_MD *get_md() const { return md_t->get_md(); }
};

#endif // CPP_MESSAGE_DIGESTS_H
