#include <stdio.h>

#define SIZE 99

int main()
{
    int c, x, y, grid[SIZE][SIZE], vis[SIZE][SIZE];

    x = y = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++y;
        else
            grid[y][x++ % SIZE] = c - '0';
    for (c = 0; c < SIZE; ++c) {
        vis[0][c] = 1;
        vis[c][0] = 1;
        vis[c][SIZE-1] = 1;
        vis[SIZE-1][c] = 1;
    }
    for (y = 1; y < SIZE-1; ++y)
        for (x = 1; x < SIZE-1; ++x) {
            vis[y][x] = 0;
            for (c = y-1; c >= 0; --c)
                if (grid[c][x] >= grid[y][x])
                    break;
            if (c < 0) {
                vis[y][x] = 1;
                continue;
            }
            for (c = y+1; c < SIZE; ++c)
                if (grid[c][x] >= grid[y][x])
                    break;
            if (c == SIZE) {
                vis[y][x] = 1;
                continue;
            }
            for (c = x-1; c >= 0; --c)
                if (grid[y][c] >= grid[y][x])
                    break;
            if (c < 0) {
                vis[y][x] = 1;
                continue;
            }
            for (c = x+1; c < SIZE; ++c)
                if (grid[y][c] >= grid[y][x])
                    break;
            if (c == SIZE) {
                vis[y][x] = 1;
                continue;
            }
        }
    c = 0;
    for (y = 0; y < SIZE; ++y)
        for (x = 0; x < SIZE; ++x)
            if (vis[y][x] == 1)
                ++c;
    printf("%d\n", c);
    return 0;
}
