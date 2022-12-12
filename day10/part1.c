#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 16

int getline(char line[], int maxline);

int main()
{
    int len, val, cycles, i, x, sum;
    char line[MAXLINE];

    x = 1;
    sum = 0;
    cycles = -19;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (line[0] == 'a')
            i = 2;
        else
            i = 1;
        for (; i > 0; --i, ++cycles)
            if (cycles % 40 == 0)
                sum += (cycles+20) * x;
        x += atoi(line + 4);
    }
    printf("%d\n", sum);
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
