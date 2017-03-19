#include <stdint.h>
#include <memory.h>
#include <malloc.h>

typedef long long int int64;


void encode_des(char *str, char *key);
int64 init_permutation(int64 n);
int expansion(int n);
void s_box(int n);
int64 to_int64(char *str);

int main() {
    char *test = "fayazsan";
    printf("%lld", to_int64(test));
    return 0;
};

int64 to_int64(char *str) {
    int64_t num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = (num << 8) | str[i];
    }
    return num;
}

void encode_des(char *str, char *key) {

}

int64 init_permutation(int64 n) {
    int64 tmp = 0;
    for (int i = 0; i < 64; i++) {
    }
    return tmp;
}

int expansion(int n) {
    return n;
}

void s_box(int n) {}
