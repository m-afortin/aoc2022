#include <stdio.h>

#define MAXLINE 8
#define TOPSIZE 3

int getline(char line[], int maxline);
int atoi(char line[]);
int sort(int arr[], int size);

int main()
{
    int i, len, cur, tmp, max[TOPSIZE];
    char line[MAXLINE];

    cur = 0;
    for (i = 0; i < TOPSIZE; ++i)
        max[i] = 0;
    while ((len = getline(line, MAXLINE)) > 0)
        if (len == 1) {
            if (cur > max[0])
                max[0] = cur;
            sort(max, TOPSIZE);
            cur = 0;
        } else
            cur += atoi(line);
    for (i = 0, cur = 0; i < TOPSIZE; ++i)
        cur += max[i];
    printf("%d\n", cur);
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

/* atoi: convert line of input to integer;
 * assume line is a positive integer */
int atoi(char line[])
{
    char *c;
    int n;
    
    for (n=0, c=line; *c!='\0' && *c!='\n'; ++c) {
        n *= 10;
        n += (*c - '0');
    }
    return n;
}

/* sort: sort array of integers */
int sort (int arr[], int size)
{
    int i, tmp;

    for (i = 0; i < size-1; ++i) {
        tmp = arr[i];
        if (tmp > arr[i+1]) {
            arr[i] = arr[i+1];
            arr[i+1] = tmp;
        }
    }
}
