#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NAMELENGTH 41
#define NROOMS 10

char namebuf[NAMELENGTH];
int outfile = -1;

void freeRoom(int roomno) {
    off_t offset;
    size_t nwrite;

    if (outfile == -1 && (outfile = open("residents", O_WRONLY)) == -1) {
        printf("Error occured!");
        return;
    }

    offset = (roomno - 1) * NAMELENGTH;

    char blank[NAMELENGTH];

    for (int i = 0; i < NAMELENGTH; i++) {
        blank[i] = ' ';
    }

    if (lseek(outfile, offset, SEEK_SET) == -1) {
        printf("Error occured!");
        return;
    }
    if ((nwrite = write(outfile, blank, NAMELENGTH)) != NAMELENGTH) {
        printf("Error occured!");
        return;
    }
}

void addGuest(int roomno) {
    off_t offset;
    size_t nwrite;

    if (outfile == -1 && (outfile = open("residents", O_WRONLY)) == -1) {
        printf("Error occured!");
        return;
    }

    offset = (roomno - 1) * NAMELENGTH;

    char *blank = "NewGuest                                 ";

    if (lseek(outfile, offset, SEEK_SET) == -1) {
        printf("Error occured!");
        return;
    }
    if ((nwrite = write(outfile, blank, NAMELENGTH)) != NAMELENGTH) {
        printf("Error occured!");
        return;
    }
}

void main() {
    int j;

    freeRoom(3);
    addGuest(3);
}

