#include <stdio.h>

#define BUFSIZE 4

int main()
{
    int c, i, j, k;
    char buf[BUFSIZE];

    c = getchar();
    for (i = 0; i < BUFSIZE; ++i)
        buf[i] = c;
    k = 1;
    while ((c = getchar()) != EOF && c != '\n') {
        buf[k++ % BUFSIZE] = c;
        for (i = 0; i < BUFSIZE-1; ++i) {
            for (j = i+1; j < BUFSIZE; ++j)
                if (buf[i] == buf[j])
                    break;
            if (j != BUFSIZE)
                break;
        }
        if (j == BUFSIZE) {
            printf("%d\n", k);
            break;
        }
    }
    return 0;
}
