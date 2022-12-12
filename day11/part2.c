#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXLINE 64
#define MAXITEMS 64
#define MONKEYS 8
#define LINES 7
#define ROUNDS 10000

typedef struct monkey {
    char op;
    int val;
    int test;
    int mtrue;
    int mfalse;
    int count;
    int items[MAXITEMS];
    int inspected;
} Monkey;

int getline(char line[], int maxline);

int main()
{
    int len, i, j, k, mod;
    double val, x, y;
    char *c, line[MAXLINE];
    Monkey *m, *n, monkeys[MONKEYS];

    memset(monkeys, 0, sizeof(monkeys));
    for (i = 0; (len = getline(line, MAXLINE)) > 0; ++i) {
        j = i / LINES;
        switch (i % LINES) {
            case 1:
                m = &monkeys[j];
                strtok(line, ":");
                for (; (c = strtok(NULL, ",")); ++m->count)
                    m->items[m->count] = atoi(c);
                break;
            case 2:
                monkeys[j].op = line[23];
                monkeys[j].val = atoi(line + 25);
                break;
            case 3:
                monkeys[j].test = atoi(line + 21);
                break;
            case 4:
                monkeys[j].mtrue = atoi(line + 29);
                break;
            case 5:
                monkeys[j].mfalse = atoi(line + 30);
                break;
        }
    }
    mod = 1;
    for (i = 0; i < MONKEYS; ++i)
        mod *= monkeys[i].test;
    for (i = 0; i < ROUNDS; ++i) {
        for (j = 0; j < MONKEYS; ++j) {
            m = &monkeys[j];
            for (k = 0; k < m->count; ++k) {
                if (m->val == 0)
                    val = m->items[k];
                else
                    val = m->val;
                if (m->op == '*')
                    val *= m->items[k];
                else
                    val += m->items[k];
                val = fmod(val, mod);
                ++m->inspected;

                if (fmod(val, m->test) == 0)
                    n = &monkeys[m->mtrue];
                else
                    n = &monkeys[m->mfalse];
                n->items[n->count++] = val;
            }
            m->count = 0;
        }
    }
    x = y = 0;
    for (i = 0; i < MONKEYS; ++i) {
        if (monkeys[i].inspected > y)
            y = monkeys[i].inspected;
        if (y > x) {
            val = x;
            x = y;
            y = val;
        }
    }
    printf("%.0f\n", x * y);
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
