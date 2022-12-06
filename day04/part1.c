#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 16

typedef struct rangepair {
    int a, b, x, y;
} RangePair;

int getline(char line[], int maxline);
RangePair getrangepair(char line[]);
int fullycontains(RangePair p);

int main()
{
    int len, result;
    char line[MAXLINE];

    result = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        result += fullycontains(getrangepair(line));
    printf("%d\n", result);
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

/* getrangepair: get pair of ranges ab,xy from line */
RangePair getrangepair(char line[])
{
    RangePair p;

    p.a = atoi(strtok(line, "-"));
    p.b = atoi(strtok(NULL, ","));
    p.x = atoi(strtok(NULL, "-"));
    p.y = atoi(strtok(NULL, "\n"));
    return p;
}

/* fullcontains: range ab is fully contained by xy or vice-versa */
int fullycontains(RangePair p)
{
    if (p.a >= p.x && p.b <= p.y)
        return 1;
    else if (p.x >= p.a && p.y <= p.b)
        return 1;
    else
        return 0;
}
