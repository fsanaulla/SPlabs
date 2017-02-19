#include <malloc.h>
#include "crypto/crypto.c"

int main() {
    char test[] = "Fayaz";
    char key[] = "Fayaz";

    encode((char *) &test, (char *) &key);
    printf("%s\n", test);
//
//    decode((char *) &test);
//    printf("%s\n", test);
//    printf("%d\n", bitsCount('F'));
//    printf("%d", betaFunc('F'));

    return 0;
}