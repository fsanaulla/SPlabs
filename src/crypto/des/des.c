#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include "des.h"

uint64_t str_to_int64(char *str);
char* int64_to_str(uint64_t num);
uint64_t* str_to_pint64(char *str);
uint64_t message_permutation(uint64_t num, int *perm_table);
uint64_t bloc_message_expansion(uint32_t num);

int main() {
    char* test = "fayazsan";
    char* test1 = "faya";
    char* test_long = "I Love that algorithm";
    uint64_t t = str_to_int64(test);

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
 * Message permutation on 8 byte bloc
 */
uint64_t message_permutation(uint64_t num, int *perm_table) {
    uint64_t res = 0;
    int shift = 0;

    for (int i = 0; i < INT_64_SIZE; i++) {
        shift = perm_table[i] - 1;
        res |= ((num & (1L << shift)) >> shift) << i;
    }
    return res;
}

/*
 * Round message permutation on 4 byte bloc
 */
uint32_t message_round_permutation(uint32_t num) {
    uint32_t res = 0;
    int shift = 0;

    for (int i = 0; i < INT_32_SIZE; i++) {
        shift = round_permutation[i] - 1;
        res |= ((num & (1 << shift)) >> shift) << i;
    }

    return res;
}


/*
 * Message bloc expansion
 */
uint64_t bloc_message_expansion(uint32_t num) {
    uint64_t res = 0;
    int shift = 0;

    for (int i = 0; i < INT_48_SIZE; i++) {
        shift = message_expansion[i] - 1;
        res |= ((num & (1L << shift)) >> shift) << i;
    }

    return res;
}


