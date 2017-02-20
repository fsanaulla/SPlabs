#include <malloc.h>
#include <memory.h>
#include "crypto/crypto.c"

int main() {
    int len;
    char test[] = "I Love VNTU(no)";
    len = (int) strlen(test);
    char key[len];

    //encoding
    encode((char *) &test, (char *) &key);
    printf("%s\n", test);

    //decoding
    decode((char *) &test, (char *) &key);
    printf("%s\n", test);

    return 0;
}