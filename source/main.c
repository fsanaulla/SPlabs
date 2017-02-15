#include <malloc.h>
#include "crypto/crypto.h"

int main() {
    int len = 0;
    char* test = "Fayaz";
    len = (int) strlen(test);
    char key[len];

    encode(test, key);

    printf("%s\n", test);

//    decode(test, key);
//
//    printf("%s", test);

    return 0;
}