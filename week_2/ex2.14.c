#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int fileopen(const char *filename, const char *mode) {
    int fd=-1;

    if (!strcmp(mode, "r")) {
        fd = open(filename, O_RDONLY);
    } else if (!strcmp(mode, "w")) {
        fd = open(filename, O_WRONLY);
    } else if (!strcmp(mode, "rw")) {
        fd = open(filename, O_WRONLY);
    } else if (!strcmp(mode, "a")) {
        fd = open(filename, O_APPEND);
    }

    return fd;
}

int main(){
    int r = fileopen("residents", "r");
    int w = fileopen("residents", "w");
    int rw = fileopen("residents", "rw");
    int a = fileopen("residents", "a");

    printf("r: %d|w: %d|rw: %d|a: %d\n", r, w, rw, a);
}