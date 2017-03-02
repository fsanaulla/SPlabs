#include <stdio.h>

int wordCount(char c[]) {
    FILE *fp;
    char ch;
    int wn, state;
    wn = 0;

    fp = fopen(c, "r");
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
        return wn;
    }
}
