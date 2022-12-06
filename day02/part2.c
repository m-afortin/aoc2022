#include <stdio.h>

#define MAXLINE 8
#define OPPONENT (line[0] - 'A' + 1)
#define OUTCOME (line[2] - 'X')

enum outcomes { LOSE, DRAW, WIN };

int getline(char line[], int maxline);
int getscore(int opponent, int outcome);

int main()
{
    int len, score;
    char line[MAXLINE];

    score = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        score += getscore(OPPONENT, OUTCOME);
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
int getscore(int a, int outcome)
{
    int score, b;

    switch (outcome) {
    case LOSE:
        score = 0;
        b = (a != 1) ? a - 1 : 3;
        break;
    case DRAW:
        score = 3;
        b = a;
        break;
    case WIN:
        score = 6;
        b = (a != 3) ? a + 1 : 1;
        break;
    }
    return score + b;
}
