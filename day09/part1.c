#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXLINE 8
#define MAXVISITED 8192

typedef struct point {
    int x, y;
} Point;

int getline(char line[], int maxline);

int main()
{
    int len, steps, i, count;
    char line[MAXLINE];
    Point t = {0}, h = {0}, ph, visited[MAXVISITED];

    for (i = 0; i < MAXVISITED; ++i) {
        visited[i].x = 0;
        visited[i].y = 0;
    }
    count = 1;
    while ((len = getline(line, MAXLINE)) > 0) {
        steps = atoi(line + 2);
        for (; steps > 0; --steps) {
            ph = h;
            switch (line[0]) {
                case 'U':
                    h.y -= 1;
                    break;
                case 'D':
                    h.y += 1;
                    break;
                case 'L':
                    h.x -= 1;
                    break;
                case 'R':
                    h.x += 1;
                    break;
            }
            if (abs(h.x - t.x) > 1 || abs(h.y - t.y) > 1)
                t = ph;
            for (i = 0; i < count; ++i)
                if (t.x == visited[i].x && t.y == visited[i].y)
                    break;
            assert(i < MAXVISITED);
            if (i == count)
                visited[count++] = t;
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
