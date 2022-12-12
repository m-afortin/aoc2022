#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 16
#define COLS 40
#define ROWS 6

int getline(char line[], int maxline);

int main()
{
    int len, val, cycles, i, j, x;
    char line[MAXLINE], crt[ROWS][COLS];

    for (i = 0; i < ROWS; ++i)
        for (j = 0; j < COLS; ++j)
            crt[i][j] = ' ';
    x = cycles = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (line[0] == 'a')
            i = 2;
        else
            i = 1;
        for (; i > 0; --i, ++cycles)
            for (j = x; j < x + 3; ++j)
                if (j == cycles % COLS)
                    crt[cycles / COLS][cycles % COLS] = '#';
        x += atoi(line + 4);
    }
    for (i = 0; i < ROWS; ++i) {
        for (j = 0; j < COLS; ++j)
            printf("%c", crt[i][j]);
        printf("\n");
    }
    return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
