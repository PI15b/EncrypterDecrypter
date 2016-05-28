#include <openssl/md5.h>
#include <openssl/md4.h>
#include <openssl/sha.h>
#include <unistd.h>
#include <fstream>
#include "encrypt.h"

static unsigned char * ReadBytesFromFile(const QString &filename, size_t &fsize)
{
    std::fstream f(filename.toStdString().c_str(), std::ios::in | std::ios::binary);
    if(!f.is_open())
        exit(EXIT_FAILURE);
    f.seekg(0, std::ios_base::end);
    fsize = f.tellg();
    f.seekg(0, std::ios_base::beg);
    uint8_t *file = new uint8_t[fsize];
    f.read((char*)file, fsize);
    return file;
}

void SaveBytesToFile(const QString &filename, const uint8_t *bytes, size_t size)
{
    std::fstream f(filename.toStdString().c_str(), std::ios::out | std::ios::binary);
    if(!f.is_open())
        exit(EXIT_FAILURE);
    f.write((char*)bytes, size);
}

uint8_t * Encrypt(unsigned int mode, Hash hash_alg, const QString &plain_dir, const QString &cipher_dir, const QString &key_dir, Key key_type, const QString &hash_dir)
{
    size_t plain_size, key_size = static_cast<size_t>(key_type);
    uint8_t * plain_text = ReadBytesFromFile(plain_dir, plain_size);
    // Key generator begin
    uint8_t *cipher_key = new uint8_t[key_size / 8];
    for(size_t i = 0; i < key_size / 8; ++i)
        cipher_key[i] = (rand() & 0xff ^ rand() & 0xFF) << rand() % 7;
    // Key generator end
    Aes aes(mode);
    uint8_t * cipher_text = aes.encrypt(plain_text, plain_size, cipher_key, key_size);
    size_t cipher_size;
    if(mode == Aes::ECB)
        cipher_size= (plain_size - plain_size % (16)) + 16;
    else
        cipher_size = (plain_size - plain_size % (16)) + 32;
    unsigned char *hash, *key_hash;
    size_t hash_size;
    switch(hash_alg)
    {
        case Hash::MD4:
        MD4(cipher_text, cipher_size, hash);
        MD4(cipher_key, key_size / 8, key_hash);
        hash_size = MD4_DIGEST_LENGTH;
        break;
        case Hash::MD5:
        MD5(cipher_text, cipher_size, hash);
        MD5(cipher_key, key_size / 8, key_hash);
        hash_size = MD5_DIGEST_LENGTH;
        break;
        case Hash::SHA1:
        SHA1(cipher_text, cipher_size, hash);
        SHA1(cipher_key, key_size / 8, key_hash);
        hash_size = SHA_DIGEST_LENGTH;
        break;
        case Hash::SHA224:
        SHA224(cipher_text, cipher_size, hash);
        SHA224(cipher_key, key_size / 8, key_hash);
        hash_size = SHA224_DIGEST_LENGTH;
        break;
        case Hash::SHA256:
        SHA256(cipher_text, cipher_size, hash);
        SHA256(cipher_key, key_size / 8, key_hash);
        hash_size = SHA256_DIGEST_LENGTH;
        break;
        case Hash::SHA512:
        SHA512(cipher_text, cipher_size, hash);
        SHA512(cipher_key, key_size / 8, key_hash);
        hash_size = SHA512_DIGEST_LENGTH;
        break;
    }

    for(size_t i = 0; i < hash_size; ++i)
        hash[i] ^= key_hash[i];

    SaveBytesToFile(cipher_dir, cipher_text, cipher_size);
    SaveBytesToFile(key_dir, cipher_key, key_size / 8);
    SaveBytesToFile(hash_dir, hash, hash_size);
}

uint8_t * Decrypt(unsigned int mode, Hash hash_alg, const QString &plain_dir, const QString &cipher_dir, const QString &key_dir, const QString &hash_dir)
{
    size_t cipher_size, key_size, hash_size;
    uint8_t * cipher_text = ReadBytesFromFile(cipher_dir, cipher_size);
    uint8_t * cipher_key = ReadBytesFromFile(key_dir, key_size);
    uint8_t * hash = ReadBytesFromFile(hash_dir, hash_size);
    unsigned char *cipher_hash, *key_hash;
    switch(hash_alg)
    {
        case Hash::MD4:
        MD4(cipher_text, cipher_size, cipher_hash);
        MD4(cipher_key, key_size, key_hash);
        hash_size = MD4_DIGEST_LENGTH;
        break;
        case Hash::MD5:
        MD5(cipher_text, cipher_size, cipher_hash);
        MD5(cipher_key, key_size, key_hash);
        hash_size = MD5_DIGEST_LENGTH;
        break;
        case Hash::SHA1:
        SHA1(cipher_text, cipher_size, cipher_hash);
        SHA1(cipher_key, key_size, key_hash);
        hash_size = SHA_DIGEST_LENGTH;
        break;
        case Hash::SHA224:
        SHA224(cipher_text, cipher_size, cipher_hash);
        SHA224(cipher_key, key_size, key_hash);
        hash_size = SHA224_DIGEST_LENGTH;
        break;
        case Hash::SHA256:
        SHA256(cipher_text, cipher_size, cipher_hash);
        SHA256(cipher_key, key_size, key_hash);
        hash_size = SHA256_DIGEST_LENGTH;
        break;
        case Hash::SHA512:
        SHA512(cipher_text, cipher_size, cipher_hash);
        SHA512(cipher_key, key_size, key_hash);
        hash_size = SHA512_DIGEST_LENGTH;
        break;
    }
    for(size_t i = 0; i < hash_size; ++i)
        hash[i] ^= cipher_hash[i];
    if(memcmp(hash, key_hash, hash_size) != 0)
        throw "Incorrect key";
    size_t plain_size;
    Aes aes(mode);
    uint8_t * plain_text = aes.decrypt(cipher_text, cipher_size, plain_size, cipher_key, key_size * 8);
    SaveBytesToFile(plain_dir, plain_text, plain_size);
}
