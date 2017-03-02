#include <malloc.h>
#include "crypto/crypto.c"
#include "math.h"

int main() {
    int len;
    char test[] = "I Love VNTU(no)";
    int key = 95;


    //encoding
    encode((char *) &test, key);
    printf("%s\n", test);

    encode((char *) &test, key);
    printf("%s\n", test);

    return 0;
}