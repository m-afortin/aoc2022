#include <stdio.h>

#define MAXLINE 64

int getline(char line[], int maxline);
char getdupe(char a[], char b[], char c[]);

int main()
{
    int len, score, member;
    char dupe, lines[3][MAXLINE];

    score = member = 0;
    while ((len = getline(lines[member % 3], MAXLINE)) > 0) {
        if (++member % 3 == 0) {
            dupe = getdupe(lines[0], lines[1], lines[2]);
            score += (dupe >= 'a') ? dupe-'a'+1 : dupe-'A'+27;
        }
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

/* getdupe: get duplicate character from lines; \0 if none */
char getdupe(char a[], char b[], char c[])
{
    char *i, *j, *k;

    for (i = a; *i != '\n'; ++i)
        for (j = b; *j != '\n'; ++j)
            for (k = c; *k != '\n'; ++k)
                if (*i == *j && *j == *k)
                    return *i;
    return '\0';
}
