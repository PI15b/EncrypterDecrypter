#include "aes.h"
#include <algorithm>
#include <iterator>
#include <cmath>

#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

uint8_t Sbox[256] = {
  //  0    1      2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, // 0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, // 1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, // 2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, // 3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, // 4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, // 5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, // 6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, // 7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, // 8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, // 9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, // a
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, // b
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, // c
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, // d
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, // e
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  // f
};

uint8_t InvSbox[256] = {
  //  0    1      2     3     4     5     6     7     8     9     a     b     c     d     e     f
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, // 0
    0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, // 1
    0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, // 2
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, // 3
    0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, // 4
    0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, // 5
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, // 6
    0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, // 7
    0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, // 8
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, // 9
    0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, // a
    0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, // b
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f, // c
    0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, // d
    0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61, // e
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d  // f
};

uint32_t Rcon[16] = {
    0x00000000,0x00000001,0x00000002,0x00000004,
    0x00000008,0x00000010,0x00000020,0x00000040,
    0x00000080,0x0000001b,0x00000036,0x0000006c,
    0x000000d8,0x000000ab,0x0000004d,0x0000009a
};

Aes::Aes(unsigned int mode)
{
    curr_mode = mode;
}

uint8_t * Aes::encrypt(uint8_t plain_text[], size_t plain_size, uint8_t key[], size_t key_size)
{
    if(plain_text)
    {
        if(key)
            KeyExpansion(key, key_size);
        else
            throw "key_error";
        plain_size = PadPlainText(plain_text, plain_size);
        switch(curr_mode)
        {
            case ECB: return ecb_encrypt(plain_text, plain_size);
            case CBC: break;
            case CFB: break;
        }
    }
    else
        throw "plain_text_error";
}

uint8_t * Aes::decrypt(uint8_t cipher_text[], size_t cipher_size, uint8_t key[], size_t key_size)
{
    if(cipher_text)
    {
        if(key)
            KeyExpansion(key, key_size);
        else
            throw "key_error";
        switch(curr_mode)
        {
            case ECB: ecb_decrypt(cipher_text, cipher_size); break;
            case CBC: break;
            case CFB: break;
        }
    }
    else
        throw "plain_text_error";
}

size_t Aes::PadPlainText(uint8_t *&plain_text, size_t plain_size)
{
    size_t pad_size = (plain_size - plain_size % (4*Nb)) + 4*Nb;
    uint8_t *pad_text = new uint8_t[pad_size];
    memcpy(pad_text, plain_text, plain_size);
    for(size_t i = plain_size; i < pad_size - 1; ++i)
        pad_text[i] = rand() & 0xff ^ (rand() & 0xff) << rand() % 7;
    pad_text[pad_size - 1] = pad_size - plain_size;
    delete []plain_text;
    plain_text = new uint8_t[pad_size];
    memcpy(plain_text, pad_text, pad_size);
    return pad_size;
}

uint8_t * Aes::UnPadPlainText(uint8_t plain_text[], size_t pad_size)
{
    size_t plain_size = pad_size - plain_text[pad_size - 1];
    uint8_t *correct_plain_text = new uint8_t[plain_size];
    memcpy(correct_plain_text, plain_text, plain_size);
    return correct_plain_text;
}

uint8_t * Aes::ecb_encrypt(uint8_t plain_text[], size_t plain_size)
{
    uint8_t *cipher_text = new uint8_t[plain_size];
    for(size_t i = 0; i < plain_size; i+=4*Nb)
    {
        memcpy(State, plain_text + i, 4*Nb);
        AddRoundKey(0);
        for(size_t r = 1; r < Nr; ++r)
            Round(r);
        FinalRound();
        memcpy(cipher_text + i, State, sizeof(State));
    }
    return cipher_text;
}

uint8_t * Aes::ecb_decrypt(uint8_t cipher_text[], size_t cipher_size)
{
    uint8_t *plain_text = new uint8_t[cipher_size];
    for(size_t i = 0; i < cipher_size; i+=4*Nb)
    {
        memcpy(State, cipher_text + i, 4*Nb);
        AddRoundKey(Nr * Nb);
        for(size_t r = Nr - 1; r > 0; --r)
            InvRound(r);
        InvFinalRound();
        memcpy(plain_text + i, State, sizeof(State));
    }
    plain_text = UnPadPlainText(plain_text, cipher_size);
    return plain_text;
}


void Aes::Round(size_t curr_round)
{
    SubBytes();
    ShiftRows();
    MixColumns();
    AddRoundKey(curr_round * Nb);
}

void Aes::InvRound(size_t curr_round)
{
    InvShiftRows();
    InvSubBytes();
    AddRoundKey(curr_round * Nb);
    InvMixColumns();
}

void Aes::FinalRound()
{
    SubBytes();
    ShiftRows();
    AddRoundKey(Nr * Nb);
}

void Aes::InvFinalRound()
{
    InvShiftRows();
    InvSubBytes();
    AddRoundKey(0);
}

void Aes::KeyExpansion(uint8_t key[], size_t key_size)
{
    if(key_size == 128 || key_size == 192 || key_size == 256)
    {
        Nk = key_size / (8*Nb);
        Nr = Nk + Nb + 2;
        w = new uint32_t[Nb*(Nr + 1)];
        memcpy(w, key, key_size / 8);
        if(Nk < 8)
            for(size_t i = Nk; i < Nb * (Nr + 1); i+=Nk)
            {
                w[i] = w[i - Nk] ^ SubWord((w[i - 1] << 24) | (w[i - 1] >> 8)) ^ Rcon[i/Nk];
                for(size_t j = 1; j < Nk && i + j < Nb * (Nr + 1); ++j)
                    w[i + j] = w[i + j - Nk] ^ w[i + j - 1];
            }
        else
            for(size_t i = Nk; i < Nb * (Nr + 1); i+=Nk)
            {
                w[i] = w[i - Nk] ^ SubWord((w[i - 1] << 24) | (w[i - 1] >> 8)) ^ Rcon[i/Nk];
                for(size_t j = 1; j < 4; ++j)
                    w[i + j] = w[i + j - Nk] ^ w[i + j - 1];
                w[i + 4] = w[i + 4 - Nk] ^ SubWord(w[i + 3]);
                for(size_t j = 5; j < Nk && i + j < Nb * (Nr + 1); ++j)
                    w[i + j] = w[i + j - Nk] ^ w[i + j - 1];
            }
    }
    else
        throw "key_size_error";
}

uint32_t Aes::SubWord(uint32_t word)
{
    uint32_t result;
    result = Sbox[word >> 24];
    result <<= 8;
    result |= Sbox[(word >> 16) & 0xff];
    result <<= 8;
    result |= Sbox[(word >> 8) & 0xff];
    result <<= 8;
    result |= Sbox[word & 0xff];
    return result;
}

void Aes::SubBytes()
{
    for(size_t i = 0; i < Nb*4; ++i)
        State[i] = Sbox[State[i]];
}

void Aes::ShiftRows()
{
    uint8_t temp = State[1];
    State[1] = State[5];
    State[5] = State[9];
    State[9] = State[13];
    State[13] = temp;
    temp = State[2];
    uint8_t temp1 = State[6];
    State[2] = State[10];
    State[6] = State[14];
    State[10] = temp;
    State[14] = temp1;
    temp = State[15];
    State[15] = State[11];
    State[11] = State[7];
    State[7] = State[3];
    State[3] = temp;
}

void Aes::InvMixColumns() {
    uint8_t a,b,c,d;
    for (size_t i = 0; i < 4*Nb ; i+=Nb)
    {

          a = State[i];
          b = State[i + 1];
          c = State[i + 2];
          d = State[i + 3];

          State[i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^
         Multiply(c, 0x0d) ^ Multiply(d, 0x09);
          State[i + 1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^
         Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
          State[i + 2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^
         Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
          State[i + 3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^
         Multiply(c, 0x09) ^ Multiply(d, 0x0e);
    }
}

void Aes::MixColumns() {
   uint8_t Tmp,Tm,t,e,f,g,h,a,b,c,d;
   for(size_t i = 0; i < 4*Nb; i+=Nb)
   {
       a = State[i];
       b = State[i + 1];
       c = State[i + 2];
       d = State[i + 3];
       t = a;
       Tmp = a ^ b ^ c ^ d;
       Tm = a ^ b ;
       Tm = xtime(Tm);
       e = Tm ^ Tmp ^ a ;

       Tm = b ^ c;
       Tm = xtime(Tm);
       f = Tm ^ Tmp ^ b;

       Tm = c ^ d ;
       Tm = xtime(Tm);
       g = Tm ^ Tmp ^ c;

       Tm = d ^ t ;
       Tm = xtime(Tm);
       h = Tm ^ Tmp ^ d;
       State[i] = e;
       State[i + 1] = f;
       State[i + 2] = g;
       State[i + 3] = h;
   }
}

void Aes::InvSubBytes()
{
    for(size_t i = 0; i < Nb*4; ++i)
        State[i] = InvSbox[State[i]];
}

void Aes::InvShiftRows()
{
    uint8_t temp = State[13];
    State[13] = State[9];
    State[9] = State[5];
    State[5] = State[1];
    State[1] = temp;
    temp = State[14];
    uint8_t temp1 = State[10];
    State[14] = State[6];
    State[10] = State[2];
    State[6] = temp;
    State[2] = temp1;
    temp = State[3];
    State[3] = State[7];
    State[7] = State[11];
    State[11] = State[15];
    State[15] = temp;
}

void Aes::AddRoundKey(size_t index)
{
    for(size_t i = 0; i < Nb; ++i)
    {
        State[i*Nb] = State[i*Nb] ^ w[index + i] & 0xff;
        State[1 + i * Nb] = State[1 + i*Nb] ^ w[index + i] >> 8 & 0xff;
        State[2 + i * Nb] = State[2 + i*Nb] ^ w[index + i] >> 16 & 0xff;
        State[3 + i * Nb] = State[3 + i*Nb] ^ w[index + i] >> 24 & 0xff;
    }
}
