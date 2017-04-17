#include <stdint.h>
#include <memory.h>
#include <malloc.h>
#include "des.h"

int main() {
    char* test = "fayazsanaulla";
    char* test_key = "keykeyke";
    uint64_t l = 1923440L;

//    des(test, test_key);
    __u_char * res = pint64_to_string(str_to_pint64(test), 2);
    printf("%s", res);

    free(res);
    return 0;
};

/*
 * Split int64 to 2 separate int32
 */
uint32_t* split_int64(uint64_t num) {
    uint32_t* arr = (uint32_t*) malloc(2);
    arr[0] = (uint32_t) num >> 32;
    arr[1] = (uint32_t) num;
    return arr;
}

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
__u_char * int64_to_str(uint64_t* num) {
    return (__u_char *) num;
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
 * pint64 to string
 */
__u_char * pint64_to_string(uint64_t * parr, size_t _size) {
    //TODO: IMPL
    size_t str_size = _size * BYTE_SIZE;
    __u_char * result_string = (__u_char *) malloc(str_size);
    int index = 0;

//    for (int i = 0; i < _size; i++) {
//        index = BYTE_SIZE * 0;
//        result_string[index] =
//    }

    return result_string;
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
uint64_t generate_round_key(uint64_t key_64, int round) {
    uint64_t key_56 = int64_bloc_permutation(key_64, BYTE_SIZE * 7, initial_key_permutation);
    uint64_t shifted_key = key_56 << key_shift_sizes[round];
    return int64_bloc_permutation(shifted_key, BYTE_SIZE * 6, sub_key_permutation);
}

/*
 * S box substitution
 */
uint32_t sbox_substitution(uint64_t bloc) {
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

        tmpRow |= arr_6bit[j] & 1;
        tmpRow |= ((arr_6bit[j] & (1 << 5)) >> 5) << 1;

        tmpColumn |= (arr_6bit[j] & (1 << 1)) >> 1;
        tmpColumn |= ((arr_6bit[j] & (1 << 2)) >> 2) << 1;
        tmpColumn |= ((arr_6bit[j] & (1 << 3)) >> 3) << 2;
        tmpColumn |= ((arr_6bit[j] & (1 << 4)) >> 4) << 3;

        arr_4bit[j] = s_boxes[j][tmpRow][tmpColumn];
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

/*
 * DES
 */
void des(char* message, char* key) {
    //bitkey
    uint64_t bit_key = str_to_int64(key);

    size_t tmp_msg_size = strlen(message);
    size_t msg_size = 0;

    if (tmp_msg_size % 8 > 0) msg_size = tmp_msg_size / 8 + 1;
    else msg_size = tmp_msg_size / 8;

    uint64_t* message_int64 = str_to_pint64(message);

    uint32_t left = 0;
    uint32_t right = 0;
    uint64_t final_result = 0;
    uint64_t* res_int64_arr = (uint64_t*) malloc(msg_size);
//    char* res_char_arr = (char*) malloc(8);


    for (int i = 0; i < msg_size; i++) {
        final_result = 0;

        //INITIAL PERMUTATION
        uint64_t permuted_bloc = int64_bloc_permutation(message_int64[i], BYTE_SIZE * 8, initial_permutation);

        uint32_t* left_right = split_int64(permuted_bloc);
        left = left_right[0];
        right = left_right[1];

        free(left_right);

        for (int j = 0; j < 16; j++) {
            // bloc expansion
            uint64_t expanded = bloc_message_expansion(left);

            //generate round key
            uint64_t round_key = generate_round_key(bit_key, j);

            //XOR round key with expansion
            uint64_t xor_result = expanded ^ round_key;

            //sbox substitution
            uint32_t sbox_res = sbox_substitution(xor_result);

            //round permutation
            uint32_t permuted = message_round_permutation(sbox_res);

            //XOR left part with right part
            uint32_t xor_parts_result = left ^ permuted;

            //Swapping
            left = right;
            right = xor_parts_result;
        }

        final_result |= (left << 32);
        final_result |= right;

        res_int64_arr[i] = final_result;
    }

    for (int k = 0; k < msg_size; k++) {
        printf("%s\n", "debug: -> printing");
        printf("%s\n", int64_to_str(&res_int64_arr[k]));
    }

    free(res_int64_arr);
    free(message_int64);
}


