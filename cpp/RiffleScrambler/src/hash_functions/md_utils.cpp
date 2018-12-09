//
// Created by konrad on 29.11.18.
//

#include <riffle/hash_functions/md_utils.h>

#include <riffle/hash_functions/md_types.h>

#include <map>
#include <string>

const MD_Wrapper get_md_by_name(const std::string &name) {
    static const std::map<std::string, MD_Wrapper> types{
        {"sha224", MD_Wrapper{MD_Type<MD_sha224>{}}},
        {"sha256", MD_Wrapper{MD_Type<MD_sha256>{}}},
        {"sha384", MD_Wrapper{MD_Type<MD_sha384>{}}},
        {"sha512", MD_Wrapper{MD_Type<MD_sha512>{}}},
        {"sha1", MD_Wrapper{MD_Type<MD_sha1>{}}},
        {"md5", MD_Wrapper{MD_Type<MD_md5>{}}},
        {"mdc2", MD_Wrapper{MD_Type<MD_mdc2>{}}},
        {"ripemd160", MD_Wrapper{MD_Type<MD_ripemd160>{}}},
        {"blake2s256", MD_Wrapper{MD_Type<MD_blake2s256>{}}},
        {"blake2s512", MD_Wrapper{MD_Type<MD_blake2s512>{}}}};

    return types.at(name);
}
