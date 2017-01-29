#include <stdio.h>

int main() {
    FILE *fp;
    char filename[100];
    char ch;
    int wn = 0;
    int state = 0;

    printf("Введіть шлях до файлу:");
    scanf("%s", filename);

    fp = fopen(filename, "r");
    if (fp == NULL) perror("Can't open file\n");
    else {
        while ((ch = (char) getc(fp)) != EOF) {
            if (ch == ' ' || ch == '\n' || ch == '\t')
                state = 0;
            else if (state == 0) {
                state = 1;
                ++wn;
            }
        }
        printf("Кількість слів: %d\n", wn);
        return 0;
    }
}