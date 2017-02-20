void encode(char *s, char *key);
void decode(char *s, char *key);
int bentFunc(int n);
int polynomial(int n);

void encode(char *s, char *key) {
    int tmp, tmpKey;
    for (int i = 0; s[i] != '\0' ; i++) {
        tmp = s[i] << 1;
        tmp |= bentFunc(tmp);
        tmpKey = polynomial(tmp);
        key[i] = tmpKey;
        s[i] ^= tmpKey;
    }
}

void decode(char *s, char *key) {
    for (int i = 0; i < strlen(s); ++i) {
        s[i] ^= key[i];
    }
}

int bentFunc(int n) {
    return (n & 128) ^ (n & 32) ^ (n & 16) ^ (n & 2) ^ (n & 1);
}

int polynomial(int n) {
    return (n & 240) ^ (n & 112) ^ (n & 7) ^ (n & 6) ^ (n & 24) ^ (n & 1) ^ 1;
}
