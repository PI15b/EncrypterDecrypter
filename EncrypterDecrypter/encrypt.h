#ifndef ENCRYPT
#define ENCRYPT
#include <inttypes.h>
#include "Rijndael/aes.h"
#include <QString>
enum class Hash{MD4, MD5, SHA1, SHA224, SHA256, SHA512};
enum class Key{key128 = 128, key192 = 192, key256 = 256};

//Encrypt procedure
uint8_t * Encrypt(unsigned int mode, Hash hash_alg, const QString &plain_dir, const QString &cipher_dir, const QString &key_dir, Key key_type, const QString &hash_dir);
//Decrypt procedure
uint8_t * Decrypt(unsigned int mode, Hash hash_alg, const QString &plain_dir, const QString &cipher_dir, const QString &key_dir, const QString &hash_dir);


#endif // ENCRYPT

