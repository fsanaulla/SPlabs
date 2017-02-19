#include <stdio.h>

void swap(int *px, int *py);
void changeArr(char *s, int ch);

int main() {
//    int x, y, w, z;
//    x = 5;
//    y = 7;
//    swap(&x, &y);
//    printf("%d", x);
    char arr[] = "fayaz";
    changeArr(&arr, 1);
    printf("%s", arr);
};

void swap(int *px, int *py) {
    int tmp;
    tmp = *px;
    *px = *py;
    *py = tmp;
}

void changeArr(char *s, int ch) {
    for (int i = 0; s[i] != '\0'; ++i) {
        s[i] <<= ch;
    }
}