#ifndef AES_H
#define AES_H
#include <stdint.h>
#include <cstring>

class Aes
{
public:
    Aes(unsigned int mode = ECB);
    // Encrypt procedure
    uint8_t * encrypt(uint8_t plain_text[], size_t plain_size, uint8_t key[], size_t key_size);
    // Decrypt procedure
    uint8_t * decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size, uint8_t key[], size_t key_size);
    enum mode{ECB, CBC, PCBC, CFB, OFB};
    enum {Nb = 4};
private:
    struct CryptException
    {
        CryptException(char err_str[]){ strcpy(this->err_str, err_str); }
        char * what() { return err_str; }
    private:
        CryptException();
    protected:
        char *err_str;
    };
    struct KeyException: public CryptException
    {
        KeyException():CryptException("Key error"){}
    };

    struct PlainTextException: public CryptException
    {
        PlainTextException():CryptException("Plain text error"){}
    };
    struct CipherTextException: public CryptException
    {
        CipherTextException():CryptException("Cipher text error"){}
    };
    size_t Nk, Nr;
    unsigned int curr_mode;
    uint8_t State[4*Nb];
    uint32_t *w; // key schedule
    // Encrypt procedures for different block cipher modes
    uint8_t * ecb_encrypt(uint8_t plain_text[], size_t plain_size);
    uint8_t * ecb_decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size);
    uint8_t * cbc_encrypt(uint8_t plain_text[], size_t plain_size);
    uint8_t * cbc_decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size);
    uint8_t * pcbc_encrypt(uint8_t plain_text[], size_t plain_size);
    uint8_t * pcbc_decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size);
    uint8_t * cfb_encrypt(uint8_t plain_text[], size_t plain_size);
    uint8_t * cfb_decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size);
    uint8_t * ofb_encrypt(uint8_t plain_text[], size_t plain_size);
    uint8_t * ofb_decrypt(uint8_t cipher_text[], size_t cipher_size, size_t &plain_size);
    // Aes procedures
    void AddRoundKey(size_t round);
    /* void InvMixColumns();
    void InvShiftRows();
    void InvSubBytes();*/
    void MixColumns();
    void ShiftRows();
    void SubBytes();
    void InvShiftRows();
    void InvSubBytes();
    void InvMixColumns();
    uint32_t SubWord(uint32_t word);
    void KeyExpansion(uint8_t key[], size_t key_size);
    void InvRound(size_t curr_round);
    void Round(size_t curr_round);
    void InvFinalRound();
    void FinalRound();
    // Pad procedure ISO 10126
    size_t PadPlainText(uint8_t *&plain_text, size_t plain_size);
    // UnPad procedure
    uint8_t * UnPadPlainText(uint8_t plain_text[], size_t pad_size, size_t &plain_size);
    // Initialization vector generator
    uint8_t * GenInitVector();
};

#endif // AES_H
