#include <malloc.h>
#include "crypto/crypto.c"

int main() {
    char test[] = "Fayaz";
    char key[] = "Fayaz";

    //encoding
    encode((char *) &test, (char *) &key);
    printf("%s\n", test);

    //decoding
    decode((char *) &test, (char *) &key);
    printf("%s\n", test);

    return 0;
}