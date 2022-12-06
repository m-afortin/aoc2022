#include <stdio.h>

#define MAXLINE 8

int getline(char line[], int maxline);
int atoi(char line[]);

int main()
{
    int len, cur, max;
    char line[MAXLINE];

    cur = max = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len == 1) {
            if (cur > max)
                max = cur;
            cur = 0;
        } else
            cur += atoi(line);
    printf("%d\n", max);
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

/* atoi: convert line of input to integer;
 * assume line is a valid integer */
int atoi(char line[])
{
    char *c;
    int n;
    
    for (n=0, c=line; *c!='\0' && *c!='\n'; ++c) {
        n *= 10;
        n += (*c - '0');
    }
    return n;
}
