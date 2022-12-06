#include <stdio.h>

#define MAXLINE 8
#define OPPONENT (line[0] - 'A' + 1)
#define PLAYER (line[2] - 'X' + 1)

int getline(char line[], int maxline);
int getscore(int opponent, int player);

int main()
{
    int len, score;
    char line[MAXLINE];

    score = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        score += getscore(OPPONENT, PLAYER);
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

/* getscore: get rock, paper, scissors score for round */
int getscore(int a, int b)
{
    int score;

    if (a == b)
        score = 3;
    else if (b-a == 1 || b-a == -2)
        score = 6;
    else
        score = 0;
    return score + b;
}
