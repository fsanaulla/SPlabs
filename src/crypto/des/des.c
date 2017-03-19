#include <stdint.h>
#include <memory.h>
#include <malloc.h>

typedef long long int int64;


void encode_des(char *str, char *key);
int64 init_permutation(int64 n);
int expansion(int n);
void s_box(int n);
int64 to_int64(char *str);
char* to_char_array(int64 num);


int main() {
    char *test = "fayazsan";
    int64 res_int64 = to_int64(test);
    printf("%lld\n", res_int64);

    char *res_char = to_char_array(res_int64);
    printf("%s\n", res_char);

    free(res_char);
    return 0;
};

int64 to_int64(char *str) {
    int64_t num = 0;
    for (int i = 0; i < 8; i++) {
        num = (num << 8) | str[i];
    }
    return num;
}

char* to_char_array(int64 num) {
    char* str = (char *) malloc(8);
    for (int i = 0; i < 8; i++) {
        str[7 - i] = (char) ((num >> i * 8) & 255);
    }
    return str;
}
//todo: impl parser from string to array of int64
int64 * to_array_of_int64(char *str) {
//    int size = (int) (strlen(str) / 4);
//    int64 *arr = (int64 *) malloc((size_t)(strlen(str) / 4));
//    return arr;
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
