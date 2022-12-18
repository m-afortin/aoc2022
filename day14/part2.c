#include <stdio.h>
#include <string.h>

#define MAXLINE 256
#define PADDING 500
#define COLS (517 - 459 + 1 + PADDING)
#define ROWS (169 + 1 + 2)
#define COLOFFSET (459 - PADDING/2)

int getline(char line[], int maxline);

int main()
{
    int x, y, px, py, len, step;
    char *c, line[MAXLINE], grid[ROWS][COLS];

    for (y = 0; y < ROWS-1; ++y)
        for (x = 0; x < COLS; ++x)
            grid[y][x] = '.';
    for (x = 0; x < COLS; ++x)
        grid[ROWS-1][x] = '#';
    while ((len = getline(line, MAXLINE)) > 0) {
        px = py = 0;
        c = strtok(line, " -> ");
        while (c && sscanf(c, "%d,%d", &x, &y)) {
            grid[y][x-COLOFFSET] = '#';
            for (; px != 0 && x != px; (px < x) ? ++px : --px)
                grid[py][px-COLOFFSET] = '#';
            for (; py != 0 && y != py; (py < y) ? ++py : --py)
                grid[py][px-COLOFFSET] = '#';
            px = x;
            py = y;
            c = strtok(NULL, " ->\n");
        }
    }
    x = 500 - COLOFFSET;
    px = -1;
    y = 0;
    py = -1;
    step = 0;
    while (px != x || py != y) {
        px = x;
        py = y;
        grid[y][x] = '+';
        if (grid[y+1][x] == '.') {
            grid[y][x] = '.';
            grid[++y][x] = '+';
        } else if (grid[y+1][x-1] == '.') {
            grid[y][x] = '.';
            grid[++y][--x] = '+';
        } else if (grid[y+1][x+1] == '.') {
            grid[y][x] = '.';
            grid[++y][++x] = '+';
        } else {
            grid[y][x] = 'o';
            x = 500 - COLOFFSET;
            y = 0;
            ++step;
        }
        if (x <= 0 || x > COLS - 1)
            break;
        if (y > ROWS - 1)
            break;
    }
#if 0
    for (y = 0; y < ROWS; ++y) {
        for (x = 0; x < COLS; ++x)
            printf("%c", grid[y][x]);
        printf("\n");
    }
#endif
    printf("%d\n", step);
    return 0;
}

/* getline: read a line into s, return length */ int getline(char s[], int lim)
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
