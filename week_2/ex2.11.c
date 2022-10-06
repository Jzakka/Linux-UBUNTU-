#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define NAMELENGTH 41
#define NROOMS 10

char namebuf[NAMELENGTH];
int infile = -1;
int outfile = -1;

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

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("USAGE: [path]/ex2.11.c [FUNCTION] [ROOM_NUMBER]\n");
        exit(0);
    }
    int roomNo = argv[2][0]-'0';
    char *p;
    if (!strcmp(argv[1], "getOccupier")) {
        if (p = getOccupier(roomNo))
            printf("Room %2d, %s\n", roomNo, p);
        else
            printf("Error on room %d\n", roomNo);
    } else if (!strcmp(argv[1], "freeRoom")) {
        freeRoom(roomNo);
    } else if (!strcmp(argv[1], "addGuest")) {
        addGuest(roomNo);
    } else {
        printf("[FUNCTION]: getOccupier freeRoom addGuest\n");
        exit(0);
    }
}