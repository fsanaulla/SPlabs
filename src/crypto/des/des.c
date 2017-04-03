#include <stdint.h>
#include <memory.h>
#include <malloc.h>

#define BYTE_SIZE 8

int64_t str_to_int64(char *str);
char* int64_to_str(int64_t num);
int64_t* str_to_pint64(char *str);


int main() {
    char* test = "fayazsan";
    char* test1 = "faya";
    char* test_long = "I Love that algorithm";

    int64_t* arr = str_to_pint64(test_long);
    printf("%li\n", arr[0]);
    printf("%li\n", arr[1]);
    printf("%li\n", arr[2]);
    printf("%d", (int) sizeof(arr));

    free(arr);

    return 0;
};

int64_t str_to_int64(char *str) {
    int64_t num = 0;
    for (int i = 0; i < strlen(str); i++) {
        num = (num << BYTE_SIZE) | str[i];
    }
    return num;
}

char* int64_to_str(int64_t num) {
    char* str = (char *) malloc(BYTE_SIZE);
    for (int i = 0; i < BYTE_SIZE; i++) {
        str[7 - i] = (char) ((num >> i * BYTE_SIZE) & 255);
    }
    return str;
}

int64_t* str_to_pint64(char *str) {
    size_t size = strlen(str);
    int reminder = (int) (size % BYTE_SIZE);
    int arr_size = (int) (size / BYTE_SIZE);

    int64_t* res_arr = (int64_t*) malloc((size_t)arr_size);

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
