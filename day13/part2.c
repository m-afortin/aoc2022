#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 256
#define MAXNODES 256
#define NODECOUNT 302

typedef struct node {
    int lvl;
    int val;
} Node;

int getline(char line[], int maxline);
void getnodes(char line[], Node nodes[]);
void incnode(Node *node);
int compnodes(const void *a, const void *b);

int main()
{
    int i, len, mul;
    char line[MAXLINE];
    Node *nodes[NODECOUNT];

    for (i = 0; i < NODECOUNT; ++i)
        nodes[i] = calloc(MAXNODES, sizeof(Node));
    i = 0;
    while ((len = getline(line, MAXLINE)) > 0) {
        if (len > 1)
            getnodes(line, nodes[i++]);
    }
    getnodes("[[2]]", nodes[i++]);
    getnodes("[[6]]", nodes[i++]);
    qsort(nodes, NODECOUNT, sizeof(Node *), compnodes);
    mul = 1;
    for (i = 0; i < NODECOUNT; ++i)
        if ((nodes[i][2].val == 2 || nodes[i][2].val == 6)
                && nodes[i][3].val == -2
                && nodes[i][4].val == -2)
            mul *= (i+1);
    printf("%d\n", mul);
    for (i = 0; i < NODECOUNT; ++i)
        free(nodes[i]);
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

/* compnodes: compare two nodes for qsort function */
int compnodes(const void *a, const void *b)
{
    int i;
    Node left[MAXNODES], right[MAXNODES], *l, *r;

    for (l=(*(Node **)a), i=0; l->lvl!=0 || l->val!=0; ++l, ++i)
        left[i] = *l;
    for (r=(*(Node **)b), i=0; r->lvl!=0 || r->val!=0; ++r, ++i)
        right[i] = *r;
    for (l=left+1, r=right+1; l->lvl!=0 || r->lvl!=0; ++l, ++r) {
        if (l->val == -2 && r->val != -2)
            return -1;
        if (r->val == -2 && l->val != -2)
            return 1;
        if (l->val == -1 && r->val != -1) {
            incnode(r);
            continue;
        }
        if (r->val == -1 && l->val != -1) {
            incnode(l);
            continue;
        }
        if (l->val < r->val)
            return -1;
        if (l->val > r->val)
            return 1;
    }
    return 0;
}
