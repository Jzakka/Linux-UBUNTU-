#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NAMELENGTH 41
#define NROOMS 10

char namebuf[NAMELENGTH];
int infile = -1;

char *getOccupier(int roomno) {
    off_t offset;
    size_t nread;

    if (infile == -1 && (infile = open("residents", O_RDONLY)) == -1) {
        return NULL;
    }

    offset = (roomno - 1) * NAMELENGTH;

    if (lseek(infile, offset, SEEK_SET) == -1)
        return NULL;
    if ((nread = read(infile, namebuf, NAMELENGTH)) <= 0)
        return NULL;

    namebuf[nread - 1] = '\0';
    return namebuf;
}

void main() {
    int j;
    char *getOccupier(int), *p;

    for (j = 1; j <= NROOMS; j++) {
        p = getOccupier(j);
        printf("\n%d: %s\n", j, p);
        if (!strcmp(p, "                                        ")) {
            printf("First empty Room %2d\n", j);
            break;
        }
    }
}

