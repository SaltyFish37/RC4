#include "ioput.h"

void encrypted(int *arg);
void rc4_ini(unsigned char *K, unsigned char *S, unsigned char *R, long int N);
char* rc4_crypt(unsigned char *S, char *KeyStream, char *PlainText, long int size);
