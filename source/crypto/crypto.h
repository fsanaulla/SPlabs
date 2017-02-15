#include <stdio.h>
#include <memory.h>


int bitsCount(int n) {
    int res = 0;
    while (n) {
        res += n & 1;
        n >>= 1;
    }
    return res % 2;
}

int betaFunc(int n) {
    return bitsCount(n & 240) ^ bitsCount(n & 112) ^ bitsCount(n & 7) ^ bitsCount(n & 6) ^ bitsCount(n & 24) ^ bitsCount(n & 1) ^ 1;
}
//todo fix error 139
void encode(char s[], char key[]) {
    int i, bit = 0;

    for (i = 0; s[i] != '\0'; i++) {
        s[i] <<= 1;
        bit = bitsCount(s[i]);
        s[i] |= bit;
        key[i] = betaFunc(s[i]);

        s[i] ^= key[i];
    }
}

void decode(char s[], char key[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        s[i] ^= key[i];
    }
}