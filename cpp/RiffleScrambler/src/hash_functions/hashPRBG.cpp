//
// Created by konrad on 16.11.18.
//

#include <riffle/hash_functions/EVP_MD_Context_Adapter.h>
#include <riffle/hash_functions/hashPRBG.h>

void hashPRBG::generateNewBuffor(const void *const message,
                                 const size_t message_len) {
    EVP_DigestInit_ex(ctx.getContext(), EVP_sha256(), nullptr);
    EVP_DigestUpdate(ctx.getContext(), message, message_len);
    EVP_DigestFinal_ex(ctx.getContext(), this->md, &(this->md_len));
}

hashPRBG::hashPRBG(const void *const message, const size_t message_len) {
    generateNewBuffor(message, message_len);
}

bool hashPRBG::getNextBit() {
    if (position > md_len * CHAR_BIT) {
        this->generateNewBuffor(md, md_len);
        position = 0;
    }

    bool result =
        (this->md[position / CHAR_BIT] & (1 << (position % CHAR_BIT))) > 0;
    position++;

    return result;
}
