#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256
#define MAXNODES 256

typedef struct node {
    int lvl;
    int val;
} Node;

int getline(char line[], int maxline);
void getnodes(char line[], Node nodes[]);
void incnode(Node *node);

int main()
{
    int i, pair, sum, lvl;
    char lefts[MAXLINE], rights[MAXLINE], sep[2];
    Node leftn[MAXNODES], rightn[MAXNODES], *n, *l, *r;

    sum = pair = 0;
    while (getline(lefts, MAXLINE) > 0
            && getline(rights, MAXLINE)
            && getline(sep, 2) >= 0) {
        ++pair;
        memset(leftn, 0, sizeof(leftn));
        memset(rightn, 0, sizeof(rightn));
        getnodes(lefts, leftn);
        getnodes(rights, rightn);
        l = leftn + 1;
        r = rightn + 1;
        while (l->lvl != 0 || r->lvl != 0) {
            if (l->val == -2 && r->val != -2) {
                sum += pair;
                break;
            }
            if (r->val == -2 && l->val != -2)
                break;
            if (l->val == -1 && r->val != -1) {
                incnode(r);
                continue;
            }
            if (r->val == -1 && l->val != -1) {
                incnode(l);
                continue;
            }
            if (l->val < r->val) {
                sum += pair;
                break;
            }
            if (l->val > r->val)
                break;
            ++l;
            ++r;
        }
    }
    printf("%d\n", sum);
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

/* getnodes: get list of nodes from line of input */
void getnodes(char line[], Node nodes[])
{
    char *c;
    int val, count, lvl;

    count = lvl = 0;
    for (c = line; *c != '\n'; ++c) {
        if (*c == '[') {
            nodes[count].val = -1;
            nodes[count++].lvl = lvl++;
        }else if (*c == ']') {
            nodes[count].val = -2;
            nodes[count++].lvl = --lvl;
        } else if (*c != ',') {
            if (*(c+1) >= '0' && *(c+1) <= '9')
                val = atoi(c++);
            else
                val = atoi(c);
            nodes[count].lvl = lvl;
            nodes[count++].val = val;
        }
    }
}

/* incnode: increase node level (e.g. 3 -> [3]) */
void incnode(Node *node)
{
    int val;
    Node *m, *n;

    for (m = node; m->lvl != 0; ++m)
        ;
    for (n = m+2; n > node+2; --n) {
        n->val = (n-2)->val;
        n->lvl = (n-2)->lvl;
    }
    (node+1)->val = node->val;
    (node+1)->lvl = node->lvl + 1;
    node->val = -1;
    (node+2)->val = -2;
    (node+2)->lvl = node->lvl;
}
