#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 64
#define STARTROWS 8
#define STACKS 9
#define MAXSTACK (STARTROWS * STACKS)

int getline(char line[], int maxline);
void copy(char to[], char from[]);
void pushs(char stacks[STACKS][MAXSTACK], int stack, char val);
char pops(char stacks[STACKS][MAXSTACK], int stack);
char peeks(char stacks[STACKS][MAXSTACK], int stack, int offset);

int main()
{
    int i, j, k, len;
    char *c, start[STARTROWS+1][MAXLINE];
    char stacks[STACKS][MAXSTACK];
    char line[MAXLINE];

    for (i = 0; i < STACKS; ++i)
        for (j = 0; j < MAXSTACK; ++j)
            stacks[i][j] = ' ';
    i = 0;
    while ((len = getline(line, MAXLINE)) > 1)
        copy(start[i++], line);
    for (i = 0; i < STACKS; ++i)
        for (j = STARTROWS-1; j >= 0; --j)
            stacks[i][j] = start[STARTROWS-1-j][4*i+1];
    while ((len = getline(line, MAXLINE)) > 0) {
        sscanf(line, "move %d from %d to %d", &i, &j, &k);
        len = i;
        for (; i > 0; --i)
            pushs(stacks, k-1, peeks(stacks, j-1, i));
        for (i = len; i > 0; --i)
            pops(stacks, j-1);
    }
    for (i = 0; i < STACKS; ++i) {
        for (c = stacks[i]; *c != ' '; ++c)
            ;
        printf("%c", *(c-1));
    }
    printf("\n");
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

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}

/* pushs: push val to the top of the stack */
void pushs(char stacks[STACKS][MAXSTACK], int stack, char val)
{
    char *c;

    for (c = stacks[stack]; *c != ' '; ++c)
        ;
    *c = val;
}

/* pops: pop val from the top of the stack */
char pops(char stacks[STACKS][MAXSTACK], int stack)
{
    char *c, *pc, tmp;

    for (c = stacks[stack]; *c != ' '; ++c)
        pc = c;
    tmp = *pc;
    *pc = ' ';
    return tmp;
}

/* peeks: peek val from the top of the stack - offset*/
char peeks(char stacks[STACKS][MAXSTACK], int stack, int offset)
{
    char *c;

    for (c = stacks[stack]; *c != ' '; ++c)
        ;
    c -= offset;
    return *c;
}
