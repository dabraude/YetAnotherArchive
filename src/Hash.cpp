/** Copyright David Braude 2019 */

#define OPENSSL_SUCCESS 1

#include <cstring>
#include <iostream>

#include "Hash.hpp"
#include "Log.hpp"
#include "utils.hpp"

namespace YAA {

Hash::Hash(const std::string& hash_type_name)
{
    enum YAA_HASH hash_type = YAA_HASH_UNKNOWN;
    if (hash_type_name.compare("SHA1") == 0) 
        hash_type = YAA_HASH_SHA1;
    else if (hash_type_name.compare("SHA256") == 0)
        hash_type = YAA_HASH_SHA256;
    else 
        Log().error(std::string("unknown hash function: ") + hash_type_name);

    _initialise(hash_type);
}


Hash::Hash(enum YAA_HASH hash_type)
{
    _initialise(hash_type);
}

Hash::~Hash()
{
    if (_message_digest_context)
        EVP_MD_CTX_destroy(_message_digest_context);
}


bool Hash::reset()
{
    std::memset(_digest, 0, EVP_MAX_MD_SIZE);
    int result = EVP_DigestInit_ex(_message_digest_context,
                                    _message_digest_type,
                                    nullptr);
    if (result != OPENSSL_SUCCESS) {
        Log().error("failed to initialise hash digest calculator");
        return false;
    }
    return true;
}


bool Hash::add_to_message(const char * message, std::size_t num_bytes)
{
    unsigned char * md = (unsigned char *) message;
    int result = EVP_DigestUpdate(_message_digest_context, md, num_bytes);
    if (result != OPENSSL_SUCCESS) {
        Log().error("failed to update hash digest");
        return false;
    }
    return true;
}


std::string Hash::finish()
{
    
    int result = EVP_DigestFinal_ex(_message_digest_context, (unsigned char *) _digest, nullptr);
    if (result != OPENSSL_SUCCESS) {
        Log().error("failed finalise the hash digest");
        return "";
    }
    
    return hex_dump(_digest, _digest_size);;
}




void Hash::_initialise(enum YAA_HASH hash_type)
{
    _hash_type = hash_type;
    _hash_name = nullptr;
    _message_digest_type = nullptr;
    _digest_size = 0;

    _message_digest_context = EVP_MD_CTX_create();
    if (!_message_digest_context) {
        Log().critical("failed to create hash context");
        throw "failed to create hash context";
    }

    switch (hash_type) {
        case YAA_HASH_SHA1:
            _hash_name = "SHA1";
            _message_digest_type = EVP_sha1();
            break;
        case YAA_HASH_SHA256:
            _hash_name = "SHA256";
            _message_digest_type = EVP_sha256();
            break;
        default:
            Log().debug("initialising hash with unknown hash type");
            _message_digest_type = EVP_md_null();
            return;
    }
    
    _digest_size = EVP_MD_size(_message_digest_type);
    reset();
}


std::size_t Hash::num_digest_chars() const
{
    return _digest_size * 2;
}

}