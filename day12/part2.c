#include <stdio.h>
#include <string.h>
#include <limits.h>

#define ROWS 41
#define COLS 171
#define MAXQUEUE (ROWS * COLS + 1)

typedef struct point {
    char c;
    char seen;
    int cost;
    int x;
    int y;
} Point;

int main()
{
    Point grid[ROWS][COLS];
    Point *stack[MAXQUEUE], *a, *b;
    int c, x, y, sx, sy, ex, ey, i, top, bot, lowest;

    memset(grid, 0, sizeof(grid));
    for (y = 0; y < ROWS; ++y)
        for (x = 0; x < COLS; ++x)
            grid[y][x].cost = -1;
    x = y = 0;
    while ((c = getchar()) != EOF) {
        if (c == 'S') {
            sx = x % COLS;
            sy = y;
            c = 'a' - 1;
        } else if (c == 'E') {
            ex = x % COLS;
            ey = y;
            c = 'z' + 1;
        }
        if (c == '\n')
            ++y;
        else {
            grid[y][x++ % COLS].c = c;
            grid[y][x % COLS].x = x % COLS;
            grid[y][x % COLS].y = y;
        }
    }
    grid[ey][ex].cost = 0;
    grid[ey][ex].seen = 1;
    top = 0;
    bot = 1;
    stack[0] = &grid[ey][ex];
    lowest = INT_MAX;
    while (top != bot && bot < MAXQUEUE && top < MAXQUEUE) {
        a = stack[top++];
        if (a->c == 'a' && a->cost < lowest)
            lowest = a->cost;
        if (a->x < COLS-1) {
            b = &grid[a->y][a->x+1];
            if (b->cost == -1 && a->c <= b->c + 1) {
                b->cost = a->cost + 1;
                stack[bot++] = b;
            }
        }
        if (a->y < ROWS-1) {
            b = &grid[a->y+1][a->x];
            if (b->cost == -1 && a->c <= b->c + 1) {
                b->cost = a->cost + 1;
                stack[bot++] = b;
            }
        }
        if (a->x > 0) {
            b = &grid[a->y][a->x-1];
            if (b->cost == -1 && a->c <= b->c + 1) {
                b->cost = a->cost + 1;
                stack[bot++] = b;
            }
        }
        if (a->y > 0) {
            b = &grid[a->y-1][a->x];
            if (b->cost == -1 && a->c <= b->c + 1) {
                b->cost = a->cost + 1;
                stack[bot++] = b;
            }
        }
    }
    printf("%d\n", lowest);
    return 0;
}
