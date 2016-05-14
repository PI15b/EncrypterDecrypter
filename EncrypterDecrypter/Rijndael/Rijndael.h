#ifndef RIJNDAEL_H
#define RIJNDAEL_H

class Rijndael
{
public:
    // the constructor - makes sure local things are initialized
    // it if fails, throws the string "Tables failed to initialize"
    Rijndael(void);

    enum BlockMode {
        ECB = 0, // Electronic CodeBook	  - each block independent, weak
        CBC = 1  // Cipher Block Chaining - most secure
    };

    // block and key size are in bits, legal values are 128, 192, and 256 independently.
    // NOTE: since the AES standard only uses a blocksize of 128, so we default to that
    void SetParameters(int keylength, int blocklength = 128);

    // call this before any encryption with the key to use
    void StartEncryption(const unsigned char * key);
    // encrypt a single block (default 128 bits, or unsigned char[16]) of data
    // debug_vectors are a testing hook to test the standard values
    void EncryptBlock(const unsigned char * datain, unsigned char * dataout, const unsigned char * debug_vectors = 0);
    // Call this to encrypt any length data. Note the size is in BLOCKS, so you must
    // have enough space in datain and dataout to accomodate this. Pad your data before
    // calling, preferably using the padding methods listed below.
    // Decryption must use the same mode as the encryption.
    void Encrypt(const unsigned char * datain, unsigned char * dataout, unsigned long numBlocks, BlockMode mode = CBC);

    // call this before any decryption with the key to use
    void StartDecryption(const unsigned char * key);
    // decrypt a single block (default 128 bits, or unsigned char[16]) of data
    void DecryptBlock(const unsigned char * datain, unsigned char * dataout, const unsigned char * debug_vectors = 0);
    // Call this to decrypt any length data. Note the size is in BLOCKS, so you must
    // have enough space in datain and dataout to accomodate this. Pad your data before
    // calling, preferably using the padding methods listed below. You must know the desired
    // length of the output data, since all the blocks are returned decrypted.
    // Encryption must use the same mode as the decryption.
    void Decrypt(const unsigned char * datain, unsigned char * dataout, unsigned long numBlocks, BlockMode mode = CBC);


private:

    int Nb,Nk;    // block and key length / 32, should be 4,6,or 8
    int Nr;       // number of rounds

    int state_size; // number of bytes in state

    // parameters for shifts on rows in RowShift
    // todo - note C1=1 in all cases - simplify?
    int C1,C2,C3;

    unsigned char state[64]; // the state, allocated
    unsigned char W[4*8*15]; // the expanded key

    // the transforms
    void ByteSub(void);
    void ShiftRow(void);
    void MixColumn(void);
    void InvByteSub(void);
    void InvShiftRow(void);
    void InvMixColumn(void);
    void AddRoundKey(int round);

    unsigned long RotByte(unsigned long data);
    unsigned long SubByte(unsigned long data);

    // the round functions
    void Round(int round);
    void FinalRound(int round);
    void InvRound(int round);
    void InvFinalRound(int round);

    // Key expansion code - makes local copy
    void KeyExpansion(const unsigned char * key);


}; // class Rijndael

#endif //  _RIJNDAEL_H
