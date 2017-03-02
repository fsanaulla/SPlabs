#include <math.h>
#include <malloc.h>

void encode(char *s, int key);
int bentFunc(int n);
int polynomial(int n);

int main() {
    char test[] = "I Love VNTU(no)";
    int key = 95;

    printf("Оригінал: ");
    printf("%s\n", test);

    //encoding
    printf("Зашифрованине: ");
    encode((char *) &test, key);
    printf("%s\n", test);

    printf("Дешифроване: ");
    encode((char *) &test, key);
    printf("%s\n", test);

    return 0;
}

void encode(char *s, int key) {
    for (int i = 0; s[i] != '\0' ; i++) {
        int tmp, tmpKey, res = 0, tmpVal = 0;
        for (int j = 0; j < 8; j++) {
            tmp = key << j;
            tmp |= bentFunc(tmp);
            tmpKey = polynomial(tmp);
            tmpVal = (int) pow(2, j);
            res |= (s[i] & tmpVal) ^ tmpKey;
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
