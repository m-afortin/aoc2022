#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 32
#define MAXDIRS 512
#define MAXFILES 512
#define FILESYSTEM 70000000
#define SPACENEEDED 30000000

typedef struct directory {
    char name[MAXLINE];
    struct directory *parent;
    double size;
    double tempsize;
    double accsize;
} Directory;

typedef struct file {
    char name[MAXLINE];
    int size;
    Directory *dir;
} File;

int getline(char line[], int maxline);
void accsize(Directory *dir, double acc);

int main()
{
    int i, j, len, dc, fc;
    int size, used, unused, needed, smallest;
    char *cmd, *arg, line[MAXLINE];
    Directory *cwd, dirs[MAXDIRS];
    File files[MAXFILES];

    dc = 0; /* directory count */
    fc = 0; /* file count */
    cwd = NULL;
    while ((len = getline(line, MAXLINE)) > 0)
        if (line[0] == '$') {
            cmd = strtok(line+2, " ");
            arg = strtok(NULL, "\n");
            if (strcmp(cmd, "cd") == 0) {
                if (strcmp(arg, "..") == 0)
                    cwd = cwd->parent;
                else {
                    strcpy(dirs[dc].name, arg);
                    dirs[dc].parent = cwd;
                    cwd = &dirs[dc];
                    ++dc;
                }
            }
        } else if (line[0] != 'd') {
            cmd = strtok(line, " ");
            arg = strtok(NULL, "\n");
            strcpy(files[fc].name, arg);
            files[fc].size = atoi(cmd);
            files[fc].dir = cwd;
            ++fc;
        }
    for (i = 0; i < dc; ++i) {
        dirs[i].size = 0.0f;
        dirs[i].accsize = 0.0f;
        for (j = 0; j < fc; ++j)
            if (files[j].dir == &dirs[i])
                dirs[i].size += files[j].size;
        dirs[i].tempsize = dirs[i].size;
    }
    for (i = 0; i < dc; ++i)
        accsize(&dirs[i], 0);
    used = dirs[0].size + dirs[0].accsize;
    unused = FILESYSTEM - used;
    needed = SPACENEEDED - unused;
    smallest = used;
    for (i = 0; i < dc; ++i) {
        size = dirs[i].size + dirs[i].accsize;
        if (size >= needed && size < smallest)
            smallest = size;
    }
    printf("%d\n", smallest);
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

/* accsize: accumulate directory size to its parent */
void accsize(Directory *dir, double acc)
{
    if (dir->parent)
        accsize(dir->parent, dir->tempsize + acc);
    dir->accsize += acc;
    dir->tempsize = 0;
}
