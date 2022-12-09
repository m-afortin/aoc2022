#include <stdio.h>

#define SIZE 99

int main()
{
    int c, x, y, grid[SIZE][SIZE];
    int n, s, w, e, mul, top;

    x = y = 0;
    while ((c = getchar()) != EOF)
        if (c == '\n')
            ++y;
        else
            grid[y][x++ % SIZE] = c - '0';
    for (y = 1; y < SIZE-1; ++y)
        for (x = 1; x < SIZE-1; ++x) {
            for (n = 0, c = y-1; c >= 0; --c) {
                ++n;
                if (grid[c][x] >= grid[y][x])
                    break;
            }
            for (s = 0, c = y+1; c < SIZE; ++c) {
                ++s;
                if (grid[c][x] >= grid[y][x])
                    break;
            }
            for (w = 0, c = x-1; c >= 0; --c) {
                ++w;
                if (grid[y][c] >= grid[y][x])
                    break;
            }
            for (e = 0, c = x+1; c < SIZE; ++c) {
                ++e;
                if (grid[y][c] >= grid[y][x])
                    break;
            }
            mul = n * s * w * e;
            if (mul > top)
                top = mul;
        }
    printf("%d\n", top);
    return 0;
}
