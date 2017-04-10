#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include "des.h"

int main() {
    char* test = "fayazsan";
    char* test_key = "keykeyke";

    uint64_t tmp = 25;

    printf("%d", sbox_substitution(tmp));

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
uint64_t int64_bloc_permutation(uint64_t num, int res_bloc_size, int *perm_table) {
    uint64_t res = 0;
    int shift = 0;

    for (int i = 0; i < res_bloc_size; i++) {
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

    for (int i = 0; i < BYTE_SIZE * 4; i++) {
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

    for (int i = 0; i < BYTE_SIZE * 6; i++) {
        shift = message_expansion[i] - 1;
        res |= ((num & (1L << shift)) >> shift) << i;
    }

    return res;
}

/*
 * Generate round key
 */
uint64_t generate_round_key(uint64_t key_56, int round) {
    uint64_t shifted_key = key_56 << key_shift_sizes[round];
    return int64_bloc_permutation(shifted_key, BYTE_SIZE * 6, sub_key_permutation);
}

/*
 * S box substitution
 */
uint32_t sbox_substitution(uint64_t bloc) {
    //todo: fix response type(from long to int) + getting value from S_BOX
    uint32_t res = 0;
    int arr_6bit[8];
    int arr_4bit[8];
    int tmp = 0;
    int shift = 0;
    int tmpRow = 0;
    int tmpColumn = 0;

    for (int i = 0; i < 8; i++) {
        tmp = 0;
        shift = i * 6;
        tmp |= ((bloc & (1 << shift)) >> shift) << 0;
        tmp |= ((bloc & (1 << shift + 1)) >> shift + 1) << 1;
        tmp |= ((bloc & (1 << shift + 2)) >> shift + 2) << 2;
        tmp |= ((bloc & (1 << shift + 3)) >> shift + 3) << 3;
        tmp |= ((bloc & (1 << shift + 4)) >> shift + 4) << 4;
        tmp |= ((bloc & (1 << shift + 5)) >> shift + 5) << 5;

        arr_6bit[i] = tmp;
    }

    for (int j = 0; j < 8; j++) {
        tmpRow = 0;
        tmpColumn = 0;

        tmpRow |= (arr_6bit[j] & (1 << 0)) >> 1;
        tmpRow |= ((arr_6bit[j] & (1 << 5)) >> 5) << 1;

        tmpColumn |= (arr_6bit[j] & (1 << 1)) >> 1;
        tmpColumn |= ((arr_6bit[j] & (1 << 2)) >> 2) << 1;
        tmpColumn |= ((arr_6bit[j] & (1 << 3)) >> 3) << 2;
        tmpColumn |= ((arr_6bit[j] & (1 << 4)) >> 4) << 3;
        arr_4bit[j] = s_boxes[j][tmpRow][tmpColumn + 1];
    }

    arr_4bit;

    for (int k = 0; k < 8; k++) {
        shift = k * 4;
        res |= (arr_4bit[k] & (1 << 0)) << shift;
        res |= ((arr_4bit[k] & (1 << 1)) >> 1) << shift + 1;
        res |= ((arr_4bit[k] & (1 << 2)) >> 2) << shift + 2;
        res |= ((arr_4bit[k] & (1 << 3)) >> 3) << shift + 3;
    }

    return res;
}


