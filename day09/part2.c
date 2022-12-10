#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAXLINE 8
#define MAXVISITED 8092
#define KNOTS 10

typedef struct point {
    int x, y;
} Point;

int getline(char line[], int maxline);

int main()
{
    int len, steps, i, count;
    char line[MAXLINE];
    Point rope[KNOTS], visited[MAXVISITED];

    count = 1;
    memset(rope, 0, sizeof(rope));
    memset(visited, 0, sizeof(visited));
    while ((len = getline(line, MAXLINE)) > 0) {
        steps = atoi(line + 2);
        for (; steps > 0; --steps) {
            switch (line[0]) {
                case 'U':
                    rope[0].y -= 1;
                    break;
                case 'D':
                    rope[0].y += 1;
                    break;
                case 'L':
                    rope[0].x -= 1;
                    break;
                case 'R':
                    rope[0].x += 1;
                    break;
            }
            for (i = 1; i < KNOTS; ++i) {
                if (abs(rope[i-1].x - rope[i].x) > 1 || abs(rope[i-1].y - rope[i].y) > 1) {
                    if (rope[i-1].x > rope[i].x)
                        ++rope[i].x;
                    else if (rope[i-1].x < rope[i].x)
                        --rope[i].x;
                    if (rope[i-1].y > rope[i].y)
                        ++rope[i].y;
                    else if (rope[i-1].y < rope[i].y)
                        --rope[i].y;
                }
            }
            for (i = 0; i < count; ++i)
                if (rope[KNOTS-1].x == visited[i].x && rope[KNOTS-1].y == visited[i].y)
                    break;
            assert(i < MAXVISITED);
            if (i == count)
                visited[count++] = rope[KNOTS-1];
        }
    }
    printf("%d\n", count);
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
