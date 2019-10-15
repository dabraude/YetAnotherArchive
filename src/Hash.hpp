/** Copyright David Braude 2019 */
#ifndef SRC_HASH_HPP_
#define SRC_HASH_HPP_

#include <string>
#include <openssl/evp.h>

namespace YAA {

enum YAA_HASH {
    YAA_HASH_UNKNOWN,
    YAA_HASH_SHA1,
    YAA_HASH_SHA256,
};

class Hash
{
    /* Wrapper for calculating hashs
     */
public:

    /** Creats a hash calculator for the given type.
     * 
     * current supported hashes:
     *  SHA1 
     *  SHA256
     * 
     * @param hash_type_name string of Hash type that will be computed 
     */
    Hash(const std::string& hash_type_name);
    
    /** Creats a hash calculator for the given type.
     * 
     * current supported hashes:
     *  SHA1 
     *  SHA256
     * 
     * @param hash_type type of Hash that will be computed 
     */
    Hash(enum YAA_HASH hash_type);

    /** Free the memory
     * 
     */
    ~Hash();


    /** Returns the amount of characters needed for the digest
     * 
     * @returns the number of characters for writing the digest in ASCII
     */
    std::size_t num_digest_chars() const;


    /** Resets the hash engine to be used for a hash
     *
     * @returns true if the hash was reset
     */
    bool reset();


    /** Addes characters to the message
     * 
     * @param message string to add to the message
     * @param num_bytes how many bytes are in the message
     * @returns true if the message was added
     */
    bool add_to_message(const char * message, std::size_t num_bytes);

    /** finalises the digest
     * 
     * @returns the hash digest in ascii
     */
    std::string finish();

protected:

    /** initialise the digest calculator  */ 
    void _initialise(enum YAA_HASH hash_type);

    enum YAA_HASH _hash_type; // enumerated form of the hash type
    const char * _hash_name; // string name of the hash
    std::size_t _digest_size; // number of bytes in the hash digest
    char _digest[EVP_MAX_MD_SIZE]; // digest in bytes

    /* Internal to OPENSSL */
    EVP_MD_CTX * _message_digest_context;
    const EVP_MD * _message_digest_type;
};



}

#endif // SRC_HASH_HPP_