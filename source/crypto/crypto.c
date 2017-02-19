void encode(char *s, char *key);
void decode(char *s);
int bitsCount(int n);
int betaFunc(int n);

void encode(char *s, char *key) {
    for (int i = 0; s[i] != '\0' ; ++i) {
        s[i] <<= 1;
        s[i] |= bitsCount(s[i]);
        s[i] ^= betaFunc(s[i]);
    }
}

void decode(char *s) {
    for (int i = 0; s[i] != '\0' ; ++i) {
        s[i] ^= 1;
    }
}

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
