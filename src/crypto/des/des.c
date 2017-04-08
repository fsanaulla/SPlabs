#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include "des.h"

uint64_t str_to_int64(char *str);
char* int64_to_str(uint64_t num);
uint64_t* str_to_pint64(char *str);
uint64_t message_init_permutation(uint64_t num);
uint64_t bloc_message_expansion(uint32_t num);

int main() {
    char* test = "fayazsan";
    char* test1 = "faya";
    char* test_long = "I Love that algorithm";
    uint32_t num = 1;

    printf("%li", bloc_message_expansion(num));

    return 0;
};

/*
 * char[8] to int64 conversion
 */
uint64_t str_to_int64(char *str) {
    uint64_t num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = (num << BYTE_SIZE) | str[i];
    }
    return num;
}

/*
 * int64 to char[8] pointer conversion
 */
char* int64_to_str(uint64_t num) {
    char* str = (char *) malloc(BYTE_SIZE);
    for (int i = 0; i < BYTE_SIZE; i++) {
        str[7 - i] = (char) ((num >> i * BYTE_SIZE) & 255);
    }
    return str;
}

/*
 * string to int64 array conversion
 */
uint64_t* str_to_pint64(char *str) {
    size_t size = strlen(str);
    int reminder = (int) (size % BYTE_SIZE);
    int arr_size = (int) (size / BYTE_SIZE);

    uint64_t* res_arr = (uint64_t*) malloc((size_t)arr_size);

    for (int i = 0; i < arr_size; i++) {
        int index = BYTE_SIZE * i;
        char* concat_ch = (char*) malloc(BYTE_SIZE);

        for (int j = 0; j < BYTE_SIZE; j++) {
            concat_ch[j] = str[index + j];
        }

        res_arr[i] = str_to_int64(concat_ch);

        free(concat_ch);
    }

    if (reminder > 0) {
        int resize = arr_size + 1;
        char* rem = (char*) malloc((size_t) reminder);

        strncpy(rem, str + arr_size * BYTE_SIZE, (size_t) reminder);
        realloc(res_arr, (size_t) resize);
        res_arr[resize - 1] = str_to_int64(rem);
    }

    return res_arr;
}

/*
 * Initial message permutation on 8byte bloc
 */
uint64_t message_init_permutation(uint64_t num) {
    uint64_t res = 0;

    for (int i = 0; i < BYTE_SIZE * 8; i++) {
        int index = initial_message_permutation[i];
        res |= ((num & (1 << index)) >> index) << i;
    }
    return res;
}

/*
 * Message bloc expansion
 */
uint64_t bloc_message_expansion(uint32_t num) {
    //todo: fix expansion, some type error(return 32768(1 << 15))
    uint64_t res = 0;
    int index = 0;

    for (int i = 0; i < BYTE_SIZE * 6; i++) {
        index = message_expansion[i] - 1;
        res |= ((num & (1 << index)) >> index) << i;
    }

    return res;
}
