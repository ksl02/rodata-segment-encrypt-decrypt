/**
Yes, encrypt and decrypt are the same and use hardcoded key.... 
Demonstration purposes only! This is not supposed to be a secure encryption method.
These functions take a buffer which points to the start of the segment to encrypt/decrypt.
Size is the size of the specified segment.
**/
#define DEBUG

extern "C"
{
    #ifdef DEBUG
    void encrypt(char* buffer, int size) {
    #else
    static void __attribute__((always_inline)) encrypt(char* buffer, int size) {
    #endif
        for(int i = 0; i < size; i++)
        {
            buffer[i] ^= 0x12;
        }
    }
    #ifdef DEBUG
    void decrypt(char* buffer, int size) {
    #else
    static void __attribute__((always_inline)) decrypt(char* buffer, int size) {
    #endif
        for(int i = 0; i < size; i++)
        {
            buffer[i] ^= 0x12;
        }
    }
}