#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFSIZE 512

char buff[BUFFSIZE];

int main(int argc, char *argv[]) {
    int fd;
    char filename[BUFFSIZE];
    int nread;
    int nwrite;

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if ((fd = open(argv[i], O_RDONLY)) == -1) {
                printf("Error occur! filename: %s\n", argv[i]);
                exit(0);
            }
            while ((nread = read(fd, buff, BUFFSIZE)) > 0) {
                if ((nwrite = write(1, buff, BUFFSIZE)) < nread) {
                    printf("write error!\n");
                    close(fd);
                    exit(0);
                }
            }
            if (nread == -1) {
                printf("read error!\n");
                close(fd);
                exit(0);
            }
            memset(buff, 0, sizeof buff);
        }
    } else {
        while (scanf("%s", filename)) {
            if ((fd = open(filename, O_RDONLY)) == -1) {
                printf("%s\n", strerror(errno));
                printf("Error occur! filename: %s\n", filename);
                exit(0);
            }
            while ((nread = read(fd, buff, BUFFSIZE)) > 0) {
                if ((nwrite = write(1, buff, BUFFSIZE)) <= 0) {
                    printf("write error!\n");
                    close(fd);
                    exit(0);
                }
            }
            if (nread == -1) {
                printf("read error!\n");
                close(fd);
                exit(0);

            }
            memset(buff, 0, sizeof buff);
        }
    }
}