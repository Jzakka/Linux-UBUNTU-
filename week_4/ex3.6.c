#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <errno.h>

void printAccessibity(int p, char *filename)
{
    char *perm[] = {"read", "write", "execute"};
    int _amode[] = {R_OK, W_OK, X_OK};

    if (access(filename, _amode[p]) != -1)
        printf("You can %s %s!\n", perm[p], filename);
    else
    {
        printf("You can't %s %s\n", perm[p], filename);
        if (errno == ENOENT)
            perror("Cannot find the file\n");
        else if (errno == EACCES)
            perror("You have no permission for the file\n");
        else
            perror("Something has wrong\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
        exit(1);

    char *filename = argv[1];
    printAccessibity(0, filename);
    printAccessibity(1, filename);
    printAccessibity(2, filename);
}