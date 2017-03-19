#include <malloc.h>

void encode(char *s, int key);
int bentFunc(int n);
int polynomial(int n);
int bitsCount(int n);

int main() {
    char test[] = "I Love VNTU(no)";
    int key = 123;

    printf("Original: ");
    printf("%s\n", test);

    //encoding
    printf("Encrypted: ");
    encode((char *) &test, key);
    printf("%s\n", test);

    //decoding
    printf("Decoded: ");
    encode((char *) &test, key);
    printf("%s\n", test);

    return 0;
}

void encode(char *s, int key) {
    int slicedKey = 0;
    int tmpKey = 0;
    int encryptBit = 0;

    slicedKey = key << 1;
    tmpKey = slicedKey | bitsCount(polynomial(slicedKey));
    encryptBit = bitsCount(bentFunc(tmpKey));

    for (int i = 0; s[i] != '\0'; i++) {

        int res = 0;

        for (int j = 0; j < 8; j++) {

            res |= (((s[i] & (1 << j)) >> j) ^ encryptBit) << j;

        }

        s[i] = (char) res;
    }
}

int bentFunc(int n) {
    return (n & 128) ^ (n & 32) ^ (n & 16) ^ (n & 2) ^ (n & 1);
}

int polynomial(int n) {
    return (n & 240) ^ (n & 112) ^ (n & 7) ^ (n & 6) ^ (n & 24) ^ (n & 1) ^ 1;
}

int bitsCount(int n) {
    int res = 0;
    while (n) {
        res += n & 1;
        n >>= 1;
    }
    return res % 2;
}
