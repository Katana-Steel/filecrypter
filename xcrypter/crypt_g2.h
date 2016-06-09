#ifndef __crypt_g2_h
#define __crypt_g2_h 1

extern "C" void SRotateR(int count, char *str, int length);
extern "C" void SRotateL(int count, char *str, int length);
extern "C" void GetSBox(void *sbox);
extern "C" char Encrypt(char,char);
extern "C" char Decrypt(char,char);

#endif
