#include <stdio.h>

#define MAXLINE 64

int getline(char line[], int maxline);
char getdupe(char a[], int len);

int main()
{
    int len, score;
    char dupe, line[MAXLINE];

    score = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        dupe = getdupe(line, len);
        score += (dupe >= 'a') ? dupe-'a'+1 : dupe-'A'+27;
    }
    printf("%d\n", score);
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

/* getdupe: get duplicate character from line; \0 if none */
char getdupe(char line[], int len)
{
    int i, j, half;

    half = (len-1) / 2;
    for (i = 0; i < half; ++i)
        for (j = half; j < len; ++j)
            if (line[i] == line[j])
                return line[i];
    return '\0';
}
